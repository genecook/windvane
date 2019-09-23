
int elfio_init(void **edata, char *elf_file, int for_write, unsigned long long entry_point, char *err_msg);

int elfio_add_section(void **edata, unsigned long long address,int is_data, unsigned char *dbuf,int size_in_bytes,char *err_msg);

int elf_io_section_count(void **edata);

int elfio_read_next_section(void **edata, char *name,unsigned long long *address,int *is_data,unsigned char **dbuf,int *size_in_bytes,char *err_msg, int *done);

int elfio_fini(void **edata, char *err_msg);

