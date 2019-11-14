#include <string.h>
#include <stdexcept>
#include <iostream>

#include "a64sim.h"
#include "a64SemiHosting.h"


//***************************************************************************************************
// a64 specific semihosting...go team...
//***************************************************************************************************


//***************************************************************************************************
// Dispatch - X0 - semihost op index...
//***************************************************************************************************

int a64SemiHosting::Dispatch(Packet *_packet, bool _verbose) {
  packet  = _packet;
  verbose = _verbose;

  rcode = -1;

  int semihost_op = (int) cpu->GP[0].Value();  // X0 - semihost op index

  if (verbose)
    std::cout << "[a64SemiHosting::Dispatch] semihost op: 0x" << std::hex << semihost_op << std::dec
	      << " (" << opname(semihost_op) << ")" << std::endl;
  
  switch(semihost_op) {
    case SYS_OPEN:             Open();            break;
    case SYS_CLOSE:            Close();           break;
    case SYS_WRITEC:           WriteC();          break;
    case SYS_WRITE0:           Write0();          break;
    case SYS_WRITE:            Write();           break;
    case SYS_READ:             Read();            break;
    case SYS_READC:            ReadC();           break;
    case SYS_ISERROR:          IsError();         break;
    case SYS_ISTTY:            IsTTY();           break;
    case SYS_SEEK:             Seek();            break;
    case SYS_FLEN:             Flen();            break;
    case SYS_TMPNAME:          TmpName();         break;
    case SYS_REMOVE:           Remove();          break;
    case SYS_RENAME:           Rename();          break;
    case SYS_CLOCK:            Clock();           break;
    case SYS_TIME:             Time();            break;
    case SYS_SYSTEM:           System();          break;
    case SYS_ERRNO:            Errno();           break;
    case SYS_GET_CMDLINE:      GetCmdline();      break;
    case SYS_HEAPINFO:         HeapInfo();        break;
    case SYS_ELAPSED:          Elapsed();         break;
    case SYS_TICKFREQ:         TickFreq();        break;
    case SYS_REPORT_EXCEPTION: ReportException(); break;
	
      default: if (verbose)
               std::cout << "[a64SemiHosting::Dispatch] unknown semihost op index:" << semihost_op
		         << "'" << std::endl;
      break;
  }

  if (verbose)
    std::cout << "[a64SemiHosting::Dispatch] return code: " << rcode << " (0x" << std::hex << rcode
	      << std::dec << ")" << std::endl;

  cpu->GP[0].Value(rcode); // ALWAYS set simulator return value...

  return rcode;
}


//***************************************************************************************************
// convenience methods for reading command arguments from simulator memory, writing values back...
//***************************************************************************************************

unsigned long long a64SemiHosting::ReadULL(unsigned long long src_addr) {
  unsigned char tbuf[8];

  if (ReadSimulatorMemory(src_addr,tbuf,8)) {
    char errbuf[128];
    sprintf(errbuf,"ERROR: problems reading from simulator memory, address/# of bytes: 0x%llx/%d",src_addr,8);
    throw std::runtime_error(errbuf);
  }

  unsigned long long tval = 0;
  
  memory->ApplyEndianness((unsigned char *) &tval,tbuf,packet->big_endian,8,8);

  return tval;
}

void a64SemiHosting::ReadString(unsigned char *dest, unsigned long long src_addr, int len) {
  if (ReadSimulatorMemory(src_addr,dest,len)) {
    char errbuf[128];
    sprintf(errbuf,"ERROR: problems reading from simulator memory, address/# of bytes: 0x%llx/%d",
	    src_addr,len);
    throw std::runtime_error(errbuf);
  }
}

void a64SemiHosting::WriteULL(unsigned long long dest_addr, unsigned long long src_val) {
  unsigned char tbuf[8];
  
  memory->ApplyEndianness(tbuf,(unsigned char *) &src_val,packet->big_endian,8,8);

  if (WriteSimulatorMemory(dest_addr,tbuf,8)) {
    char errbuf[128];
    sprintf(errbuf,"ERROR: problems writing to simulator memory, address/# of bytes: 0x%llx/%d",dest_addr,8);
    throw std::runtime_error(errbuf);
  }
}

void semihostParams::Dump() {
  printf("semihost parms:\n");
  printf("\tvalid?       %d\n",are_set);
  printf("\theap base:   0x%llx\n",heap_base);
  printf("\theap limit:  0x%llx\n",heap_limit);
  printf("\tstack base:  0x%llx\n",stack_base);
  printf("\tstack limit: 0x%llx\n",stack_limit);
  printf("\tenv ptr:     0x%llx\n",env_ptr);
  printf("\tcmdline ptr: 0x%llx\n",cmdline_ptr);
}

void a64SemiHosting::dumpParms() {
  params.Dump();  
}

// if any semihosting parms have been set, then they all must be set...

bool semihostParams::AreValid() {
  if ( !AreSet() /* || (heap_base==0) */  // heap could start at address 0...
       || (heap_limit==0) || (stack_base==0) || (stack_limit==0) || (env_ptr==0) || (cmdline_ptr==0) )
    return false;
  return true;
}

//***************************************************************************************************
// SYS_REPORT_EXCEPTION...
//***************************************************************************************************

void a64SemiHosting::ReportException() {
  if (verbose) std::cout << "[a64SemiHosting::ReportException] entered..." << std::endl;

  // X1 contains ptr to parms block...

  unsigned long long exc_reason_ptr = cpu->GP[1].Value(); 

  unsigned long long exc_reason = 0;

  if (exc_reason_ptr == 0) {
    // null pointer. ASSUME its time to exit the app...
    exc_reason = ADP_Stopped_ApplicationExit;
  } else {
    try {
       exc_reason = ReadULL(exc_reason_ptr);
    } catch(...) {
       std::cout << "[a64SemiHosting::ReportException] aborted. Problems reading argument block from memory?." << std::endl;
       return;
    }
  }
  
  if (verbose) std::cout << "[a64SemiHosting::ReportException] reason: 0x" <<std::hex << exc_reason << std::dec << std::endl;

  switch(exc_reason) {
    case ADP_Stopped_ApplicationExit:
      if (verbose) std::cout << "[a64SemiHosting::ReportException] application has exited..." << std::endl;
      rcode = 0x100;
      break;

    case ADP_Stopped_BranchThroughZero:
    case ADP_Stopped_SoftwareInterrupt:
    case ADP_Stopped_PrefetchAbort:
    case ADP_Stopped_DataAbort:
    case ADP_Stopped_AddressException:
    case ADP_Stopped_IRQ:
    case ADP_Stopped_FIQ:
    case ADP_Stopped_BreakPoint:
    case ADP_Stopped_WatchPoint:
    case ADP_Stopped_StepComplete:
    case ADP_Stopped_RunTimeErrorUnknown:
    case ADP_Stopped_InternalError:
    case ADP_Stopped_UserInterruption:
    case ADP_Stopped_StackOverflow:
    case ADP_Stopped_DivisionByZero:
    case ADP_Stopped_OSSpecific:

    // we don't support these yet...
    default: break;
  }
  
  if (verbose) std::cout << "[a64SemiHosting::ReportException] exited." << std::endl;
}

//***************************************************************************************************
// SYS_OPEN...
//***************************************************************************************************

void a64SemiHosting::Open() {
  if (verbose) std::cout << "[a64SemiHosting::Open] entered..." << std::endl;

  
  // X1 contains pointer into simulator (virtual) memory of sys-open arg block...
  
  unsigned long long open_args_block_ptr = cpu->GP[1].Value(); 

  
  // retreive/validate file open arguments from simulator memory...
  
  unsigned long long filename_ptr = 0;
  int mode_index = 0;
  int buflen = 0;
  unsigned char filename[SH_FILENAME_MAX_LEN];

  try {
    filename_ptr = ReadULL(open_args_block_ptr);
    mode_index   = (int) ReadULL(open_args_block_ptr + 8);
    buflen       = (int) ReadULL(open_args_block_ptr + 16) + 1; // + null string terminator

    if (verbose) {
      std::cout << "\tfilename address: 0x" << std::hex << filename_ptr << std::dec << ", length: " << buflen
	        << ", mode-index: " << mode_index << std::endl;
    }
  
    if ( (buflen <= 0) || (buflen > params.filename_max_len) )
      throw std::runtime_error("Invalid filename length");
  
    ReadString(filename,filename_ptr,buflen);

    if (strnlen((const char *) filename,params.filename_max_len) == (unsigned int) params.filename_max_len)
      throw std::runtime_error("Filename read from simulator memory is too long?");
			         
    if (verbose) std::cout << "\tfilename: '" << filename << "'" << std::endl;
  } catch(...) {
      std::cout << "[a64SemiHosting::Open] aborted. Problems reading sys-open argument block from memory?." << std::endl;
    return;
  }


  // open the file...
    
  unsigned long long filehandle = 0;

  if (semihost_helper.SysOpen((char *) filename,mode_index,filehandle)) {
    if (verbose) std::cout << "[a64SemiHosting::Open] aborted. Problems opening file." << std::endl;
    return;
  }
 
  rcode = filehandle; // filehandle IS return code...

  if (verbose) std::cout << "\tfile handle: 0x" << std::hex << filehandle << std::dec << std::endl;

  
  if (verbose) std::cout << "[a64SemiHosting::Open] exited." << std::endl;
}


//***************************************************************************************************
// SYS_CLOSE...
//***************************************************************************************************

void a64SemiHosting::Close() {
  if (verbose) std::cout << "[a64SemiHosting::Close] entered..." << std::endl;

  // X1 contains pointer into simulator (virtual) memory of sys-close arg block...
  
  unsigned long long close_args_block_ptr = cpu->GP[1].Value(); 

  if (verbose) std::cout << "[a64SemiHosting::Close] ptr: 0x" << std::hex << close_args_block_ptr << std::dec << std::endl;
  
  // retreive file handle from simulator memory...
  
  unsigned long long filehandle = 0;

  try {
    filehandle = ReadULL(close_args_block_ptr);
  } catch(...) {
      std::cout << "[a64SemiHosting::Close] aborted. Problems reading sys-close argument block from memory?." << std::endl;
    return;
  }

  if (verbose) std::cout << "\tfile handle: " << filehandle << std::endl;

  rcode = semihost_helper.SysClose(filehandle);
  
  if (verbose) std::cout << "[a64SemiHosting::Close] exited." << std::endl;
}


//***************************************************************************************************
// SYS_WRITEC...
//***************************************************************************************************

void a64SemiHosting::WriteC() {
  if (verbose) std::cout << "[a64SemiHosting::WriteC] entered..." << std::endl;
  
  // X1 contains pointer into simulator memory of character to display...
  
  unsigned long long src = cpu->GP[1].Value();

  if (!src) {
    if (verbose) std::cout << "[a64SemiHosting::WriteC] aborted. NULL src buffer ptr?." << std::endl;
    return;
  }

  // retrieve character from simulator memory...

  unsigned char tbuf[SH_STRING_MAX_LEN];

  if (ReadSimulatorMemory(src,&tbuf[0],1)) {
    if (verbose) std::cout << "[a64SemiHosting::WriteC] aborted. Problems reading input character from simulator memory?." << std::endl;
    return;
  }

  char sc = tbuf[0];
  
  if (verbose) std::cout << "[a64SemiHosting::WriteC] char to write: " << sc << std::endl;

  semihost_helper.SysWriteC(sc);
}


//***************************************************************************************************
// SYS_WRITE0...
//***************************************************************************************************

void a64SemiHosting::Write0() {
  if (verbose) std::cout << "[a64SemiHosting::Write0] entered..." << std::endl;

  // X1 contains pointer into simulator memory of string to write...
  
  unsigned long long src = cpu->GP[1].Value();

  if (!src) {
    if (verbose) std::cout << "[a64SemiHosting::Write0] aborted. NULL src buffer ptr?." << std::endl;
    return;
  }

  
  // retrieve string from simulator memory...

  // we don't know the length of the string. thus have to read from simulator memory one byte
  // at a time (ouch) 'til the nil char read...
  
  unsigned char tbuf[SH_STRING_MAX_LEN];
  int strlen = 0;
  
  for (int i = 0; i < SH_STRING_MAX_LEN; i++) {
     if (ReadSimulatorMemory(src + i,&tbuf[i],1)) {
       if (verbose)
         std::cout << "[a64SemiHosting::Write0] aborted. Problems reading input string from simulator memory?." << std::endl;
       return;
     }
     if (tbuf[i] == '\0') {
       strlen = i;
       break;
     }
  }

  if ( (strlen <= 0) || (strlen > params.string_max_len) ) {
    if (verbose)
      std::cout << "[a64SemiHosting::Write0] aborted. Input string exceeds maximum length allowed." << std::endl;
    return;
  }

  if (verbose) {
    std::cout << "\tstring to write: '" << tbuf << "'" << std::endl;
  }

  // name that tune...
  
  rcode = semihost_helper.SysWrite0((const char *) tbuf);

  
  if (verbose) std::cout << "[a64SemiHosting::SysWrite0] exited." << std::endl;
}


//***************************************************************************************************
// SYS_WRITE...
//***************************************************************************************************

void a64SemiHosting::Write() {
  if (verbose) std::cout << "[a64SemiHosting::Write] entered..." << std::endl;

  
  // X1 contains pointer into simulator (virtual) memory of sys-write arg block...

  unsigned long long write_args_block_ptr = cpu->GP[1].Value();

  // fptr[0] - file handle
  // fptr[1] - pointer to string to write
  // fptr[2] - # of bytes to write


  // retreive/validate args, src string from simulator memory...
  
  unsigned long long filehandle = 0;
  unsigned long long src_mem = 0;
  int num_bytes = 0;
  
  unsigned char membuf[SH_STRING_MAX_LEN];

  try {
    filehandle = ReadULL(write_args_block_ptr);
    src_mem    = ReadULL(write_args_block_ptr + 8);
    num_bytes  = (int) ReadULL(write_args_block_ptr + 16);

    if (verbose) {
      printf("\tfile handle: 0x%llx\n",filehandle);
      printf("\tsrc buffer: 0x%llx\n",src_mem);
      printf("\t# of bytes to write: %d\n",num_bytes);
    }

    if (!src_mem)
      throw std::runtime_error("NULL src buffer ptr?.");

    if ( (num_bytes <= 0) || (num_bytes > params.string_max_len) )
      throw std::runtime_error("# of bytes to write exceeds maximum length allowed.");

    ReadString(membuf,src_mem,num_bytes);
    
  } catch(...) {
      std::cout << "[a64SemiHosting::Write] aborted. Problems reading sys-write argument block from memory?." << std::endl;
    return;
  }

  
  // name that tune...
  
  rcode = semihost_helper.SysWrite(filehandle,(const char *) membuf,num_bytes);

  
  if (verbose) std::cout << "[a64SemiHosting::Write] exited, rcode: " << rcode << std::endl;
}


//***************************************************************************************************
// SYS_READ...
//***************************************************************************************************

void a64SemiHosting::Read() {
  if (verbose)
    std::cout << "[a64SemiHosting::Read] entered..." << std::endl;

  // X1 contains pointer into simulator (virtual) memory of sys-read args block...

  unsigned long long read_args_block_ptr = cpu->GP[1].Value();

  // fptr[0] - file handle
  // fptr[1] - pointer to string buffer
  // fptr[2] - # of bytes to read


  // retreive/validate args, src string from simulator memory...
  
  unsigned long long filehandle = 0;
  unsigned long long mem_ptr = 0;
  int num_bytes = 0;
  
  try {
    filehandle = ReadULL(read_args_block_ptr);
    mem_ptr    = ReadULL(read_args_block_ptr + 8);
    num_bytes  = (int) ReadULL(read_args_block_ptr + 16);

    if (verbose) {
      printf("\tfile handle: 0x%llx\n",filehandle);
      printf("\tbuffer ptr: 0x%llx\n",mem_ptr);
      printf("\t# of bytes to read: %d\n",num_bytes);
    }

    if (!mem_ptr)
      throw std::runtime_error("NULL read buffer ptr?.");

    if ( (num_bytes <= 0) || (num_bytes > params.string_max_len) )
      throw std::runtime_error("# of bytes to read exceeds maximum length allowed."); 
  } catch(...) {
      rcode = 0;
      if (verbose)
        std::cout << "[a64SemiHosting::Write] aborted. Problems reading sys-write argument block from memory?." << std::endl;
    return;
  }


  // read from file...

  unsigned char src[num_bytes];
  memset(src,'\0',num_bytes);

  int number_of_bytes_read = semihost_helper.SysRead(filehandle,src,num_bytes);

  if (verbose)
    std::cout << "\t# of bytes returned from file read: " << number_of_bytes_read << std::endl;

  if (number_of_bytes_read == num_bytes) {
    // read the # of bytes we expected...
    rcode = 0;
  } else if (number_of_bytes_read == 0) {
    // we think this means EOF???
    rcode = num_bytes; // 0?
  } else if ( (number_of_bytes_read < 0) || (number_of_bytes_read > num_bytes) ) {
    // # of bytes read is negative? or greater than the # requested?
    rcode = num_bytes; // 0?
  } else {
    // partial read so return the # of bytes read...
    rcode = num_bytes - number_of_bytes_read;
  }

  
  // then write to simulator memory...

  WriteSimulatorMemory(mem_ptr,src,num_bytes);
  
  if (verbose) std::cout << "[a64SemiHosting::Read] exited." << std::endl;
}


//***************************************************************************************************
// SYS_READC...
//***************************************************************************************************

void a64SemiHosting::ReadC() {
  char rc = (char) semihost_helper.SysReadC();

  if (verbose)
    std::cout << "[a64SemiHosting::ReadC] char read:" << rc << std::endl;  

  rcode = (unsigned long long) rc;
}


//***************************************************************************************************
// SYS_ISERROR...
//***************************************************************************************************

void a64SemiHosting::IsError() {
  // X1 contains pointer into simulator (virtual) memory of is-error args block...

  unsigned long long args_block_ptr = cpu->GP[1].Value();

  // retreive status word from simulator memory...
  
  long long status_word = 0;

  try {
    status_word = (long long) ReadULL(args_block_ptr);
    if (verbose) printf("\tstatus word: %lld\n",status_word);
  } catch(...) {
    std::cout << "[a64SemiHosting::IsError] aborted. Problems reading status word from memory?." << std::endl;
    return;
  }

  // then check it...
  
  rcode = (unsigned long long) semihost_helper.IsError(&status_word);
}


//***************************************************************************************************
// SYS_ISTTY...
//***************************************************************************************************

void a64SemiHosting::IsTTY() {
  if (verbose) std::cout << "[a64SemiHosting::IsTTY] entered..." << std::endl;

  // X1 - pointer to stored filehandle...
  
  unsigned long long args_block_ptr = cpu->GP[1].Value(); 

  
  // retreive filehandle from simulator memory...

  unsigned long long filehandle = 0;

  try {
    filehandle = ReadULL(args_block_ptr);
  } catch(...) {
    std::cout << "[a64SemiHosting::IsError] aborted. Problems reading filehandle from memory?." << std::endl;
    return;
  }

  if (verbose) std::cout << "\tfilehandle: 0x" << std::hex << filehandle << std::dec << std::endl;


  // then check it...
  
  int is_tty = semihost_helper.IsTTY(filehandle);

  rcode = is_tty;

  if (verbose) std::cout << "[a64SemiHosting::IsTTY] exited, is-tty? " << is_tty << std::endl;
}


//***************************************************************************************************
// SYS_SEEK...
//***************************************************************************************************

void a64SemiHosting::Seek() {
  // X1 contains pointer into simulator (virtual) memory of sys-seek args block...

  unsigned long long args_block_ptr = cpu->GP[1].Value();

  // fptr[0] - file handle
  // fptr[1] - byte position to seek to

  unsigned long long filehandle = 0;
  unsigned long long byte_position = 0;

  try {
    filehandle    = ReadULL(args_block_ptr);
    byte_position = ReadULL(args_block_ptr + 8);
    
    if (verbose) {
      printf("\tfile handle: 0x%llx\n",filehandle);
      printf("\tbyte position: 0x%llx\n",byte_position);
    }
  } catch(...) {
      std::cout << "[a64SemiHosting::Write] aborted. Problems reading sys-seek argument block from memory?."
		<< std::endl;
    return;
  }
  
  rcode = semihost_helper.SysSeek(filehandle,byte_position);
}


//***************************************************************************************************
// SYS_FLEN...
//***************************************************************************************************

void a64SemiHosting::Flen() {
  // X1 - pointer to stored filehandle...
  
  unsigned long long args_block_ptr = cpu->GP[1].Value(); 

  
  // retreive filehandle from simulator memory...

  unsigned long long filehandle = 0;

  try {
    filehandle = ReadULL(args_block_ptr);
  } catch(...) {
    std::cout << "[a64SemiHosting::Flen] aborted. Problems reading filehandle from memory?." << std::endl;
    return;
  }

  if (verbose) std::cout << "\tfilehandle: 0x" << std::hex << filehandle << std::dec << std::endl;


  // then get file object length...
  
  int flen = semihost_helper.SysFlen(filehandle);

  rcode = flen;

  if (verbose)
    std::cout << "[a64SemiHosting::Flen] file handle: 0x" << std::hex << filehandle
	      << std::dec << ", file length: " << rcode << std::endl;
}


//***************************************************************************************************
// SYS_CLOCK...
//***************************************************************************************************

void a64SemiHosting::Clock() {
  rcode = (unsigned long long) semihost_helper.SysClock();

  if (verbose)
    std::cout << "[a64SemiHosting::Clock] clock: 0x" << std::hex << rcode << std::dec << std::endl;
}


//***************************************************************************************************
// SYS_TIME...
//***************************************************************************************************

void a64SemiHosting::Time() {
  rcode = (unsigned long long) semihost_helper.SysTime();

  if (verbose)
    std::cout << "[a64SemiHosting::Time] time: 0x" << std::hex << rcode << std::dec << std::endl;
}


//***************************************************************************************************
// SYS_ERRNO...
//***************************************************************************************************

void a64SemiHosting::Errno() {
  rcode = (unsigned long long) semihost_helper.SysErrNo();

  if (verbose)
    std::cout << "[a64SemiHosting::Errno] errno: 0x" << std::hex << rcode << std::dec << std::endl;
}


//***************************************************************************************************
// SYS_GETCMDLINE...
//***************************************************************************************************

void a64SemiHosting::GetCmdline() {
  if (verbose) std::cout << "[a64SemiHosting::GetCmdline] entered..." << std::endl;
  
  unsigned long long cmdline_args_block_ptr = cpu->GP[1].Value(); // pointer to pointer to cmdline block

  if (verbose) printf("\tptr to get-cmdline args: 0x%llx\n",cmdline_args_block_ptr);

  // retrieve cmdline ptr from simulator memory,
  // get buffer length (do not exceed)...

  unsigned long long cmdline_ptr = 0;

  int buflen = 0;

  try {
     cmdline_ptr = ReadULL(cmdline_args_block_ptr);
     buflen = (int) ReadULL(cmdline_args_block_ptr + 8);
  } catch(...) {
    std::cout << "[a64SemiHosting::GetCmdline] aborted. Problems reading cmdline args from memory?." << std::endl;
    return;
  }

  if (verbose) printf("\tcommand line buffer address: 0x%llx\n",cmdline_ptr);
  if (verbose) printf("\tcommand line buffer length: %d\n",buflen);


  if (buflen < (int) strlen(params.cmdline)) {
    if (verbose)
      std::cout << "[a64SemiHosting::GetCmdline] aborted. cmdline length exceeds app cmdline buffer size." << std::endl;
    return;
  }
  
  if (verbose) printf("[SYS_GET_CMDLINE] cmdline: <%s> length: %d  (max length: %d)\n",
	 params.cmdline,(int) strlen(params.cmdline),params.cmdline_max_len);
  
  // copy cmdline to simulator memory...

  if (WriteSimulatorMemory(cmdline_ptr,(unsigned char *) params.cmdline,buflen)) {
    if (verbose)
      std::cout << "[a64SemiHosting::GetCmdline] aborted. Problems writing cmdline to simulator memory." << std::endl;
    return;
  }

  // also update buffer size to reflect string length...
 
  WriteULL(cmdline_args_block_ptr + 8,strlen(params.cmdline));
  
  rcode = 0;
  
  if (verbose) std::cout << "[a64SemiHosting::GetCmdline] exited." << std::endl;
}


//***************************************************************************************************
// SYS_HEAPINFO...
//***************************************************************************************************

void a64SemiHosting::HeapInfo() {
  if (verbose) std::cout << "[a64SemiHosting::HeapInfo] entered..." << std::endl;

  
  // for this particular semihosting call, the 'C environment' options must be fully specified...

  if (params.AreSet()) {
    // semihosting parameters have been set from command line...
  } else {
    // crash and burn...
    char errbuf[1024];
    sprintf(errbuf,"ERROR: [From SYS_HEAPINFO] 'C environment' command line options have not been specified.");
    throw std::runtime_error(errbuf);
  }
  
  if (params.AreValid()) {
    // semihosting parameters have been set from command line, and appear to be valid...
  } else {
    // crash and burn...
    char errbuf[1024];
    sprintf(errbuf,"ERROR: [From SYS_HEAPINFO] One or more 'C environment' command line options have not been specified.");
    throw std::runtime_error(errbuf);
  }

  
  unsigned long long heapinfo_block_ptr = cpu->GP[1].Value(); // pointer to pointer to heap info struct

  if (verbose) printf("[SYS_HEAPINFO] ptr to heap-base ptr: 0x%llx\n",heapinfo_block_ptr);

  
  // retrieve heap info struct ptr from simulator memory,
  //   then write heap info to simulator memory...

  unsigned long long dest = 0;

  try {
    // access the value in X1 as the address of the heapinfo block...
    dest = ReadULL(heapinfo_block_ptr);
    
    if (verbose) printf("[SYS_HEAPINFO] heap-info struct address: 0x%llx\n",dest);
    
    WriteULL(dest,      params.heap_base);
    WriteULL(dest + 8,  params.heap_limit);
    WriteULL(dest + 16, params.stack_base);
    WriteULL(dest + 24, params.stack_limit);
    WriteULL(dest + 32, params.env_ptr);
    WriteULL(dest + 40, params.cmdline_ptr);
    
  } catch(...) {
    std::cout << "[SYS_HEAPINFO] aborted. Problems writing heap info to simulator memory?." << std::endl;    
  }
    
  if (verbose) {
    printf("[SYS_HEAPINFO] heap-base address/value:   0x%llx/0x%llx\n",dest,params.heap_base);
    printf("[SYS_HEAPINFO] heap-limit address/value:  0x%llx/0x%llx\n",dest + 8,params.heap_limit);
    printf("[SYS_HEAPINFO] stack-base address/value:  0x%llx/0x%llx\n",dest + 16,params.stack_base);
    printf("[SYS_HEAPINFO] stack-limit address/value: 0x%llx/0x%llx\n",dest + 24,params.stack_limit);
    printf("[SYS_HEAPINFO] env address/value:         0x%llx/0x%llx\n",dest + 32,params.env_ptr);
    printf("[SYS_HEAPINFO] cmdline address/value:     0x%llx/0x%llx\n",dest + 40,params.cmdline_ptr);
  }

  
  // write env buffer to simulator memory...
  
  if (WriteSimulatorMemory(params.env_ptr,(unsigned char *) params.env,params.env_max_len)) {
    if (verbose)
      std::cout << "[SYS_HEAPINFO] aborted. Problems writing env buffer to simulator memory." << std::endl;
    return;
  }
  

  // write cmdline buffer to simulator memory...
  
  if (WriteSimulatorMemory(params.cmdline_ptr,(unsigned char *) params.cmdline,params.cmdline_max_len)) {
    if (verbose)
      std::cout << "[SYS_HEAPINFO] aborted. Problems writing env buffer to simulator memory." << std::endl;
    return;
  }

  
  rcode = 0;

  if (verbose) std::cout << "[a64SemiHosting::HeapInfo] exited." << std::endl;
}


//***************************************************************************************************
// opname...
//***************************************************************************************************

std::string a64SemiHosting::opname(int semihost_op) {
  std::string opn = "?";
  
  switch(semihost_op) {
    case SYS_OPEN:             opn = "SYS_OPEN";             break;
    case SYS_CLOSE:            opn = "SYS_CLOSE";            break;
    case SYS_WRITEC:           opn = "SYS_WRITEC";           break;
    case SYS_WRITE0:           opn = "SYS_WRITE0";           break;
    case SYS_WRITE:            opn = "SYS_WRITE";            break;
    case SYS_READ:             opn = "SYS_READ";             break;
    case SYS_READC:            opn = "SYS_READC";            break;
    case SYS_ISERROR:          opn = "SYS_ISERROR";          break;
    case SYS_ISTTY:            opn = "SYS_ISTTY";            break;
    case SYS_SEEK:             opn = "SYS_SEEK";             break;
    case SYS_FLEN:             opn = "SYS_FLEN";             break;
    case SYS_TMPNAME:          opn = "SYS_TMPNAME";          break;
    case SYS_REMOVE:           opn = "SYS_REMOVE";           break;
    case SYS_RENAME:           opn = "SYS_RENAME";           break;
    case SYS_CLOCK:            opn = "SYS_CLOCK";            break;
    case SYS_TIME:             opn = "SYS_TIME";             break;
    case SYS_SYSTEM:           opn = "SYS_SYSTEM";           break;
    case SYS_ERRNO:            opn = "SYS_ERRNO";            break;
    case SYS_GET_CMDLINE:      opn = "SYS_GET_CMDLINE";      break;
    case SYS_HEAPINFO:         opn = "SYS_HEAPINFO";         break;
    case SYS_ELAPSED:          opn = "SYS_ELAPSED";          break;
    case SYS_TICKFREQ:         opn = "SYS_TICKFREQ";         break;
    case SYS_REPORT_EXCEPTION: opn = "SYS_REPORT_EXCEPTION"; break;
      
    default: break;
  }

  return opn;
}

//***************************************************************************************************
// read/write simulator memory...
//***************************************************************************************************

int a64SemiHosting::ReadSimulatorMemory(unsigned long long address,unsigned char *dest, int num_bytes) {
  if (verbose) printf("[a64SemiHosting::ReadSimulatorMemory] address: 0x%llx, num-bytes: %d\n",address,num_bytes);
  bool is_data = (memory->AccessType(address) == DATA);
  return memory->ReadMemory(cpu,packet,address,is_data,cpu->Privileged(),num_bytes,true,dest,false);
}

int a64SemiHosting::WriteSimulatorMemory(unsigned long long address,unsigned char *src, int num_bytes) {
  if (verbose) printf("[a64SemiHosting::WriteSimulatorMemory] address: 0x%llx, num-bytes: %d\n",address,num_bytes);
  bool is_data = (memory->AccessType(address) == DATA);
  return memory->WriteMemory(cpu,packet,address,is_data,cpu->Privileged(),num_bytes,true,src);
}





