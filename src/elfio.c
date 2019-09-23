#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <unistd.h>
#include <string.h>

#include <libelf.h>
#include <gelf.h>

// elf string table structure + routines to manage same...

struct string_table { 
  char *snames;
  int   nbytes;
};

void init_string_table(struct string_table *stab);
int add_section_name(struct string_table *stab,char *secname);


// elf_data - structure to manage elf descriptors...

struct elf_data {
  char                 filename[1024];      // the elf file
  int                  fd;                  // file descriptor
  Elf                 *e;                   // base elf descriptor
  Elf64_Ehdr          *ehdr;                // elf executable header 
  Elf64_Phdr          *phdr;                // elf program header
  Elf64_Shdr          *shdr;                // elf section header
  Elf_Scn             *scn;                 // current elf section
  Elf_Data            *data;                // current elf section data
  int                  section_count;       // # of sections
  struct string_table  section_names;       // section names elf string table
  int                  string_table_index;  // section names string table section index
  Elf_Scn             *stab_scn;            // string table section handle (for reader)
  int                  for_write;           // true if writing to elf file
  char                *section_name;        // pointer to 'next' section name
  unsigned char       *section_read_buffer; // holds 'next' section data when reading elf file 
  int                  num_bytes;           // # of bytes in read buffer
  void                **sec_names;          // memory allocated for section names
};


// elfio_abort - called in face of elf errors...

int elfio_abort(void **edata,char *errmsg) {
  struct elf_data *ed = (struct elf_data *) *edata;
  if (ed) {
    if (ed->e) elf_end(ed->e);
    if (ed->fd >= 0) close(ed->fd);
    free (*edata);
    *edata = NULL;
  }
  return -1;
}


//----------------------------------------------------------------------------------------------------------
// elfio_init - open file for write. allocate/initialize ELF file structures...
//----------------------------------------------------------------------------------------------------------

int elfio_init_for_write(void **edata, char *err_msg, unsigned long long entry_point);
int elfio_init_for_read(void **edata, char *err_msg);

int elfio_init(void **edata, char *elf_file, int _for_write, unsigned long long entry_point, char *err_msg) {
  struct elf_data *ed = (struct elf_data *) (*edata = malloc(sizeof(struct elf_data)));

  strcpy(ed->filename,elf_file);

  ed->fd   = -1;

  ed->e    = NULL;
  ed->scn  = NULL;
  ed->data = NULL;
  ed->ehdr = NULL;
  ed->phdr = NULL;
  ed->shdr = NULL;

  ed->section_count = 0;

  init_string_table(&ed->section_names);

  ed->for_write = _for_write;

  ed->string_table_index = -1;

  ed->stab_scn = NULL;

  ed->section_name = NULL;

  ed->section_read_buffer = NULL;

  ed->num_bytes = 0;

  /* check ELF version... */

  if (elf_version(EV_CURRENT) == EV_NONE) {
    sprintf(err_msg,"ELF library initialization failed: %s\n",elf_errmsg(-1));
    return elfio_abort(edata,err_msg);
  }

  if (ed->for_write)
    return elfio_init_for_write(edata,err_msg,entry_point);
  else
    return elfio_init_for_read(edata,err_msg);
}

//----------------------------------------------------------------------------------------------------------
// elfio_init_for_write
//----------------------------------------------------------------------------------------------------------

int elfio_init_for_write(void **edata, char *err_msg, unsigned long long entry_point) {
  struct elf_data *ed = (struct elf_data *) *edata;

  /* create file descriptor for write... */

  if ((ed->fd = open(ed->filename,O_WRONLY|O_CREAT , 0777)) < 0) {
    sprintf(err_msg,"File open failed, output file: '%s'",ed->filename);
    return elfio_abort(edata,err_msg);
  }

  /* get ELF descriptor for creating new ELF objects: */

  if ((ed->e = elf_begin(ed->fd,ELF_C_WRITE ,NULL)) == NULL) {
    sprintf(err_msg,"Failed to get ELF descriptor: %s.",elf_errmsg(-1));
    return elfio_abort(edata,err_msg);
  }

  /* allocate ELF executable header: */

  if ((ed->ehdr = elf64_newehdr(ed->e)) == NULL) {
    sprintf(err_msg,"Failed to allocate ELF executable header: %s.",elf_errmsg(-1));
    return elfio_abort(edata,err_msg);
  }

  ed->ehdr->e_ident[EI_DATA] = ELFDATA2LSB;  /* big endian (vs ELFDATA2LSB) */
  ed->ehdr->e_machine        = EM_AARCH64;   /* EM_386;                     */
  ed->ehdr->e_type           = ET_EXEC;      /* ELF executable              */
  ed->ehdr->e_version        = EV_CURRENT;

  ed->ehdr->e_entry          = entry_point;  /* set entry point */

  /* allocate ELF program header with a single entry. will be upated later on...*/

  if ((ed->phdr = elf64_newphdr(ed->e, 1)) == NULL) {
    sprintf(err_msg,"Failed allocate ELF program header: %s.",elf_errmsg ( -1));
    return elfio_abort(edata,err_msg);
  }

  return 0;
}

//----------------------------------------------------------------------------------------------------------
// elfio_init_for_read
//----------------------------------------------------------------------------------------------------------

int elfio_init_for_read(void **edata, char *err_msg) {
  struct elf_data *ed = (struct elf_data *) *edata;

  /* create file descriptor for read... */

  if ((ed->fd = open(ed->filename,O_RDONLY,0)) < 0) {
    sprintf(err_msg,"File open failed, file: '%s'",ed->filename);
    return elfio_abort(edata,err_msg);
  }

  /* get ELF descriptor for creating new ELF objects: */

  if ((ed->e = elf_begin(ed->fd,ELF_C_READ ,NULL)) == NULL) {
    sprintf(err_msg,"Failed to get ELF descriptor: %s.",elf_errmsg(-1));
    return elfio_abort(edata,err_msg);
  }

  if (elf_kind(ed->e) != ELF_K_ELF) {
    sprintf(err_msg,"%s does not appear to be in ELF format.",ed->filename);
    return elfio_abort(edata,err_msg);
  }

  /* get index of section names (string table) section index */

  if (elf_getshdrstrndx(ed->e, (size_t *) &ed->string_table_index) != 0) {
    sprintf(err_msg,"Failed to get string table section index: %s.",elf_errmsg(-1));
    return elfio_abort(edata,err_msg);
  }

  /* for performance reasons, get handle to elf string table only once... */

  if ((ed->stab_scn = elf_getscn(ed->e, ed->string_table_index)) == NULL) {
    sprintf(err_msg,"Failed to get string table section handle: %s.",elf_errmsg(-1));
    return elfio_abort(edata,err_msg);
  }

  ed->scn = NULL;  /* prime 'next section' pointer */

  printf("elf reader initialized...\n");
  fflush(stdout);
  
  GElf_Ehdr ehdr;
  
  if (gelf_getehdr(ed->e, &ehdr) == NULL) {
     warnx("gelf_getehdr failed: %s", elf_errmsg(-1));
     return -1;
  }

  ed->section_count = ehdr.e_shnum;
  
  printf("total # of sections: %d\n", ed->section_count);
  
  return 0;
}

int elf_io_section_count(void **edata) {
  struct elf_data *ed = (struct elf_data *) *edata;

  return ed->section_count;
}

//----------------------------------------------------------------------------------------------------------
// elfio_add_section - add new instruction or data section to file.
//----------------------------------------------------------------------------------------------------------

int elfio_add_section(void **edata, unsigned long long address,int is_data, unsigned char *dbuf,
                      int size_in_bytes,char *err_msg) {

  struct elf_data *ed = (struct elf_data *) *edata;

  /* create section descriptor for a section to contain the 'hash' values */

  if ((ed->scn = elf_newscn(ed->e)) == NULL) {
    sprintf(err_msg,"Failed to create new ELF section: %s.",elf_errmsg(-1));
    return elfio_abort(edata,err_msg);
  }

  /* create data member for new section... */

  if ((ed->data = elf_newdata(ed->scn)) == NULL) {
    sprintf(err_msg,"Failed to create data member for new ELF section: %s.",elf_errmsg(-1));
    return elfio_abort(edata,err_msg);
  }

  ed->data->d_align   = 1;     // byte aligned always...
  ed->data->d_off     = 0;
  ed->data->d_buf     = dbuf;
  ed->data->d_type    = ELF_T_BYTE;
  ed->data->d_size    = size_in_bytes;
  ed->data->d_version = EV_CURRENT;

  /* fill out section header... */

  if ((ed->shdr = elf64_getshdr(ed->scn)) == NULL) {
    sprintf(err_msg,"Failed to create new ELF section header: %s.",elf_errmsg(-1));
    return elfio_abort(edata,err_msg);
  }

  // make all sections 'PROGBITS', else when test is loaded, data sections are ignored (at least in
  // arm foundation model anyway)...
  
  ed->shdr->sh_type    = SHT_PROGBITS;   // is_data ? SHT_HASH : SHT_PROGBITS;
  
  ed->shdr->sh_flags   = SHF_ALLOC | SHF_EXECINSTR;
  ed->shdr->sh_entsize = 0;
  ed->shdr->sh_addr    = address;

  ed->section_count += 1;

  /* form new section name, add to section header... */

  char section_name[1024];

  sprintf(section_name,".%s%d",(is_data ? "data" : "text"),ed->section_count);

  ed->shdr->sh_name = add_section_name(&ed->section_names,section_name);

  return 0;
}

//----------------------------------------------------------------------------------------------------------
// elfio_read_next_section - read section data into (allocated) data buffer...
//
//   NOTE: size_in_bytes == 0 when there are no more sections to read.
//----------------------------------------------------------------------------------------------------------

/* standard elf_strptr gets handle to string table section every time its called */
/* and thus for a large elf file is quite slow...                                */

char *elfio_strptr(void **edata, size_t offset) {
   struct elf_data *ed = (struct elf_data *) *edata;

   GElf_Shdr shdr;

   gelf_getshdr(ed->stab_scn,&shdr);

   Elf_Data *d = NULL;
   d = elf_getdata(ed->stab_scn,d);

   if (offset >= d->d_off && offset < d->d_off + d->d_size)
     return ((char *) d->d_buf + offset - d->d_off);

   return NULL;
}

int elfio_read_next_section(void **edata, char *name,unsigned long long *address,int *is_data,
                            unsigned char **dbuf,int *size_in_bytes,char *err_msg,int *done) {

  //printf("[elfio_read_next_section] entered...\n");
  //fflush(stdout);

  struct elf_data *ed = (struct elf_data *) *edata;

  strcpy(name,"");      /* initialize section name, */
  *dbuf = NULL;         /*   section data pointer,  */
  *size_in_bytes = 0;   /*     # of bytes read      */

  if (ed->section_read_buffer != NULL) {
    free(ed->section_read_buffer);       /* free up memory     */
    ed->section_read_buffer = NULL;      /* from previous read */
  }

  if ((ed->scn = elf_nextscn(ed->e,ed->scn)) == NULL) {
    /* no more sections... */
    //printf("[elfio_read_next_section] no more sections...\n");
    *done = 1;
    return 0;
  }

  //printf("  get section header...\n");
  //fflush(stdout);

  /* get section header... */

  GElf_Shdr shdr; /* we'll just keep a local copy of this 'generic' header... */
  
  if (gelf_getshdr(ed->scn,&shdr) != &shdr) {
    sprintf(err_msg,"Failed to obtain next ELF section header: %s.",elf_errmsg(-1));
    return elfio_abort(edata,err_msg);
  }

  //printf("  lookup section name...\n");
  //fflush(stdout);

  /* lookup section name in string table section. ASSUME all valid sections are named... */

  if ((ed->section_name = elfio_strptr(edata,shdr.sh_name)) == NULL) {
    sprintf(err_msg,"Failed to obtain next ELF section name: %s.",elf_errmsg(-1));
    return elfio_abort(edata,err_msg);
  }

  //printf(">>>section name: '%s'\n",ed->section_name);
  
  //printf("  cycle thru section %s (size: %ld)...\n", ed->section_name,shdr.sh_size);
  //fflush(stdout);
  
  /* cycle thru section data, growing 'read buffer' 'til done... */

  ed->data = NULL;
  ed->num_bytes = 0;

  while ( (ed->num_bytes < shdr.sh_size) && ((ed->data = elf_getdata(ed->scn,ed->data)) != NULL) && (ed->data->d_buf != NULL) ) {
    //printf("    next block: 0x%llx, size: %ld, data ptr: 0x%llx...\n",
    //       ed->data,ed->data->d_size,ed->data->d_buf);
    //fflush(stdout);

    if (ed->section_read_buffer == NULL)
      ed->section_read_buffer = malloc(ed->data->d_size);
    else
      ed->section_read_buffer = realloc(ed->section_read_buffer,ed->num_bytes + ed->data->d_size);

    //printf("    next block allocated: new size: %ld...\n",ed->num_bytes + ed->data->d_size);
    //fflush(stdout);
  
    memcpy(&ed->section_read_buffer[ed->num_bytes],ed->data->d_buf,ed->data->d_size);
    ed->num_bytes += ed->data->d_size;
  }

  //printf("  copy section name...\n");
  //fflush(stdout);

  strcpy(name,ed->section_name); /* copy section name */

  *address = shdr.sh_addr;  /* pick off section address from section header */
  *is_data = ( (shdr.sh_type == SHT_PROGBITS) || (shdr.sh_type == SHT_NOBITS) ) ? 1 : 0; /* we think PROGBITS or NOBITS indicates 'real' data or instrs */

  *dbuf = ed->section_read_buffer;
  *size_in_bytes = ed->num_bytes;

  //printf("[elfio_read_next_section] exited.\n");
  //fflush(stdout);

  return 0;
}

//----------------------------------------------------------------------------------------------------------
// elfio_fini
//----------------------------------------------------------------------------------------------------------

int elf_writer_fini(void **edata, char *err_msg);
int elf_reader_fini(void **edata, char *err_msg);

int elfio_fini(void **edata, char *err_msg) {

  struct elf_data *ed = (struct elf_data *) *edata;

  if (ed->for_write) 
    return elf_writer_fini(edata,err_msg);
  else
    return elf_reader_fini(edata,err_msg);
}

//----------------------------------------------------------------------------------------------------------
// elf_writer_fini
//----------------------------------------------------------------------------------------------------------

int elf_writer_fini(void **edata, char *err_msg) {

  struct elf_data *ed = (struct elf_data *) *edata;

  /* create section, section header to hold string table... */

  if ((ed->scn = elf_newscn(ed->e)) == NULL) {
    sprintf(err_msg,"Failed to create ELF string table section: %s.",elf_errmsg(-1));
    return elfio_abort(edata,err_msg);
  }
  if ((ed->data = elf_newdata(ed->scn)) == NULL) {
    sprintf(err_msg,"Failed on ELF string table creation: %s.",elf_errmsg(-1));
    return elfio_abort(edata,err_msg);
  }
  if ((ed->shdr = elf64_getshdr(ed->scn)) == NULL) {
    sprintf(err_msg,"Failed to create new ELF section header: %s.",elf_errmsg(-1));
    return elfio_abort(edata,err_msg);
  }

  char section_name[128];
  strcpy(section_name,".shstrtab");

  ed->shdr->sh_name = add_section_name(&ed->section_names,section_name);

  ed->data->d_align   = 1;
  ed->data->d_buf     = ed->section_names.snames;
  ed->data->d_off     = 0LL;
  ed->data->d_size    = ed->section_names.nbytes;
  ed->data->d_type    = ELF_T_BYTE;
  ed->data->d_version = EV_CURRENT;

  if ((ed->shdr = elf64_getshdr(ed->scn)) == NULL) {
    sprintf(err_msg,"Failed to create string table section  header: %s.",elf_errmsg(-1));
    return elfio_abort(edata,err_msg);
  }

  ed->shdr->sh_type    = SHT_STRTAB;
  ed->shdr->sh_flags   = SHF_STRINGS | SHF_ALLOC;
  ed->shdr->sh_entsize = 0;

  /* set string table index field in elf executable header */

  elf_setshstrndx(ed->e,elf_ndxscn(ed->scn)); 

  /* now fill in ELF program header table entry values: */

  ed->phdr->p_type   = PT_PHDR;
  ed->phdr->p_offset = ed->ehdr->e_phoff;
  ed->phdr->p_filesz = elf64_fsize(ELF_T_PHDR , 1, EV_CURRENT );

  (void) elf_flagphdr(ed->e, ELF_C_SET , ELF_F_DIRTY );

  /* write the ELF object file out: */

  if (elf_update(ed->e, ELF_C_WRITE) < 0) {
     errx(EX_SOFTWARE , "elf_update (ELF_C_WRITE) failed: %s.",elf_errmsg(-1));
     return elfio_abort(edata,err_msg);
  }

  /* close up, we're done! */

  (void) elf_end(ed->e);
  (void) close(ed->fd);

  if (ed->section_names.snames != NULL) 
    free(ed->section_names.snames);

  return 0;
}

//----------------------------------------------------------------------------------------------------------
// elf_reader_fini
//----------------------------------------------------------------------------------------------------------

int elf_reader_fini(void **edata, char *err_msg) {
  /* close up, we're done! */

  struct elf_data *ed = (struct elf_data *) *edata;

  (void) elf_end(ed->e);
  (void) close(ed->fd);

  return 0;
}

//----------------------------------------------------------------------------------------------------------
// maintain ELF string table to hold section names...
//----------------------------------------------------------------------------------------------------------

void init_string_table(struct string_table *stab) {
  stab->snames = calloc(1,1);  // string table consists of nil, 
  stab->nbytes = 1;            //   followed by nil-terminated strings...
}

int add_section_name(struct string_table *stab,char *secname) {
  int sname_offset = stab->nbytes; // always add new string at the end...

  // grow the table by the length of the new entry + nil char...

  stab->nbytes += strlen(secname) + 1;                              
  stab->snames = (char *) realloc((void *) stab->snames,stab->nbytes); 

  // copy the section name (including its nil terminator char) into the string table...
 
  memcpy((void *) &stab->snames[sname_offset],(void *) secname,strlen(secname) + 1);

  // return the offset into the string table for the new entry...
  
  return sname_offset;
}
  

