#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <vector>

#include "SemiHosting.h"

using namespace std;

//*************************************************************************************************
/*! \mainpage notitle
 *
 * The <b>a64sim</b> simulator supports the notion of <i>semihosting</i>* whereby certain assembly
 * language instructions are recognized and trapped by the simulator, in order to communicate
 * with the host operating system. In this simulation the Halt (HLT) instruction with an immediate
 * field value of 0xfff is used to indicate a semihosted operation is desired. An example
 * assembly language sequence to write a single character to the console is below:
 *
 * \code
 *     mov X0,#3     # semihosting call index is 0x03 for SYS_WRITEC
 *     mov X1,'H'    # character to write is 'H'
 *     HLT #0xfff    # simulator recognizes this instruction encoding as a semihosting request
 * \endcode
 *
 * The simulator itself will support the semihosting calls as defined by the public methods of the
 * <i>SemiHosting</i> class. A C Aarch64 runtime library in turn will also be made available to
 * allow the simulated C program to make semihosting calls. 
 *
 * Although the simulator will recognize and field the semihosting operation, the exception caused
 * by the execution of the Halt instruction will allowed. A transparent exception handler will also 
 * be made available, to <i>skip</i> past the Halt instruction, without altering the registers
 * involved in the semihosting operation. 
 *
 * *NOTE: The phrase <i>semihosting</i> seems to have been coined by someone at ARM (at least from a quick
 * <i>google</i> search). However the idea of trapping on a machine instruction to a host or emulator for 
 * debug or system access has been around for a long time. The calls/methods described herein follow loosely 
 * the calls described in the <a href="http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0471c/Bgbjjgij.html">ARM Compiler toolchain</a> docs...
 * 
 */
//*************************************************************************************************


//*************************************************************************************************
/*! \brief Translate open mode index (used in semihosting call) to character string used with system
 * SysOpen call.
 *
 * @param[in] mode_index Integer index indicating read or write mode.
 * @param[out] mode File create mode as character string as per <i>fopen</i>.
 *
 * \returns Zero if index is valid, minus one otherwise.
 */
//*************************************************************************************************

int SemiHosting::SysOpenMode(char *mode,int mode_index) {
  int rcode = -1;

  if (mode == NULL) {
    // null ptr to (dest) mode str???
  } else {
    strcpy(mode,"?");
    switch(mode_index) {
      case 0:  strcpy(mode,"r");    rcode = 0; break;
      case 1:  strcpy(mode,"rb");   rcode = 0; break;
      case 2:  strcpy(mode,"r+");   rcode = 0; break;  
      case 3:  strcpy(mode,"r+b");  rcode = 0; break;

      case 4:  strcpy(mode,"w");    rcode = 0; break;
      case 5:  strcpy(mode,"wb");   rcode = 0; break;
      case 6:  strcpy(mode,"w+");   rcode = 0; break;
      case 7:  strcpy(mode,"w+b");  rcode = 0; break;
                                                     
      case 8:  strcpy(mode,"a");    rcode = 0; break;
      case 9:  strcpy(mode,"ab");   rcode = 0; break;
      case 10: strcpy(mode,"a+");   rcode = 0; break;
      case 11: strcpy(mode,"a+b");  rcode = 0; break;

      default: break;
    }
  }

  //printf("[SysOpenMode] index: %d mode: '%s'\n",mode_index,mode);

  return rcode;
}

//*************************************************************************************************
/*! \brief Opens a file on the host system.
 *
 * Open a file on the host system, using a relative or absolute file path. Use ':tt' for \e stdin
 * or \e stdout, depending on the open mode. See <b>C fopen</b> call for supported modes.
 * @param[out] fileHandle The fileHandle argument is the address where the file handle 
 * returned by the system fopen call is to be stored. The value is stored as a 64 bit unsigned value.
 * @param[in] filename The relative or absolute path to the file to be accessed (a null terminated
 * string).
 * @param[in] mode_index - An integer index that corresponds to the <b>C fopen mode</b> argument.
 * \returns Zero (0) if no errors, minus one (-1) for invalid input parameter(s), minus two (-2) 
 * if the <i>file open</i> operation fails.
 */
//*************************************************************************************************

int SemiHosting::SysOpen(char *filename, int mode_index, unsigned long long &file_no) {
  //printf("[SysOpen] file: '%s', mode-index: %d\n",filename,mode_index);
									 
  char mode[128];
  
  int rcode = SysOpenMode(mode,mode_index);

  FILE *fd = NULL;

  if (rcode < 0) {
    // invalid mode index...
  } else if (!strcmp(filename,":tt")) {
    bool is_read = (mode_index <= 3); // cheated, ie, looked at the code above...
    fd = is_read ? stdin : stdout;
    rcode = 0;
  } else { 
    fd = fopen(filename,mode);
    rcode = (fd != NULL) ? 0 : rcode;
  }

  if (fd == NULL) {
    //printf("[SysOpen] failed?\n"); 
  } else {
     file_no = (unsigned long long) fileno(fd);
  }
  
  return rcode;
}

//*************************************************************************************************
/*! \brief Close a file on the host system.
 *
 * @param[in] fileHandle A pointer to the file handle for an existing, ie, already opened file.
 * \returns Zero (0) if no errors, minus one (-1) fileHandle does not point to a valid file handle,
 * or if there are problems when the <i>file close</i> operation fails.
 */
//*************************************************************************************************

int SemiHosting::SysClose(unsigned long long fileHandle) {
  int rcode = -1;

  int fd = (int) fileHandle;

  switch(fd) {
    case STDIN_FILENO:
    case STDOUT_FILENO:
    case STDERR_FILENO:  // stdin or stdout. don't bother to close...
                         rcode = 0;
                         break;
			 
    default:             rcode = close(fd);
                         break;
  }
  
  return rcode;
}

//*************************************************************************************************
/*! \brief Writes a character (byte) to the debug \e channel.
 *
 * In lieue of a designated <i>debug channel</i>, the character is written to \e stdout.
 * @param[in] src_cchar The character to write. 
 * \returns Zero (0) if no errors, minus one (-1) if the \e write operation fails.
 */
//*************************************************************************************************

int SemiHosting::SysWriteC(char src_cchar) {

  int rcode = (putchar(src_cchar) == EOF) ? -1 : 0;

  return rcode;
}

//*************************************************************************************************
/*! \brief Writes a null-terminated string to the debug \e channel.
 *
 * In lieue of a designated <i>debug channel</i>, the string is written to \e stdout.
 * @param[in] src_str Pointer to the string to be written.
 * \returns Zero (0) if no errors, minus one (-1) if the input parameter is null or points to an
 * invalid character string (not terminated by a null character within \e MAX_STRING_LENGTH bytes), or the 
 * \e write operation fails. 
 */
//*************************************************************************************************

int SemiHosting::SysWrite0(const char *src_str) {
  int rcode = 0;

  if (src_str == NULL) {
    // empty input string???
    rcode = -1;
  } else {
    rcode = (fputs(src_str,stdout) == EOF) ? -1 : 0;
  }

  return rcode;
}

//*************************************************************************************************
/*! \brief Writes a null-terminated string to the specified (open) file, at the current file
 *  position
 * @param[in] fileHandle A pointer to the file handle for an existing, ie, already opened file.
 * @param[in] src_str Pointer to the string to be written.
 */
//*************************************************************************************************

int SemiHosting::SysWrite(unsigned long long fileHandle, const char *src_str, int num_bytes) {
  int rcode = -1;

  int fd = (int) fileHandle;

  rcode = (write(fd,src_str,num_bytes) == num_bytes) ? 0 : 1; 
  
  return rcode;
}

//*************************************************************************************************
/*! \brief Read <i>N</i> bytes from an open file.
 * @param[in] fileHandle A pointer to the file handle for an existing, ie, already opened file.
 * @param[in] dest_buffer Pointer to the string to be written.
 * @param[in] num_bytes The number of bytes to read from the file. 
 * \returns The number of bytes read. Zero for end of file.
 */
//*************************************************************************************************

int SemiHosting::SysRead(unsigned long long fileHandle, unsigned char *dest_buffer, int num_bytes) {
  int num_bytes_read = -1;

  int fd = (int) fileHandle;

  num_bytes_read = (int) read(fd,dest_buffer,num_bytes);

  return num_bytes_read;
}

//*************************************************************************************************
/*! \brief Read a byte from the console.
 * \returns The byte read from the console (stdin).
 */
//*************************************************************************************************

int SemiHosting::SysReadC() {
  return getchar();
}

//*************************************************************************************************
/*! \brief Check error code from some previous semihosting operation.
 * @param[in] errcode A pointer to the error code to check. The error code is stored as a 32-bit
 * signed integer.
 * \returns Zero if the error code does not indicate an error.
 */
//*************************************************************************************************

int SemiHosting::IsError(long long *errcode) {
  return (errcode != NULL) && (*errcode != 0);
}
//*************************************************************************************************
/*! \brief Checks whether a file is connected to an interactive device.
 * @param[in] fileHandle A pointer to the file handle for an existing, ie, already opened file.
 * \returns Zero if the file handle identifies a file, one if the file handle identifies an
 * interactive device. Any other value indicates an error.
 */
//*************************************************************************************************

int SemiHosting::IsTTY(unsigned long long fileHandle) {
  int rcode = -1;

  int fd = (int) fileHandle;

  switch(fd) {
    case STDIN_FILENO:
    case STDOUT_FILENO:
    case STDERR_FILENO:  // stdin or stdout or stderr. lets say yes...
                         rcode = 1;
                         break;
			 
    default:             if (fcntl(fd,F_GETFD) >= 0)
			   rcode = 0;
                         break;
  }

  return rcode;
}

//*************************************************************************************************
/*! \brief Seeks to a specified position within a file, from the start of the file.
 * @param[in] fileHandle A pointer to the file handle for an existing, ie, already opened file.
 * @param[in] byte_position The byte index from the start of the file to seek to.
 * \returns Zero if the seek was successful, a negative value otherwise. Use <i>SysErrno</i> to
 * obtain the host error code <i>errno</i>.
 */
//*************************************************************************************************

int SemiHosting::SysSeek(unsigned long long fileHandle, unsigned long long byte_position) {
  int rcode = -1;

  int fd = (int) fileHandle;

  rcode = (lseek(fd,SEEK_SET,byte_position) == (off_t) byte_position) ? 0 : 1;
  
  return rcode;
}

//*************************************************************************************************
/*! \brief Returns the length of a file, in bytes
 * @param[in] fileHandle A pointer to the file handle for an existing, ie, already opened file.
 * \returns A positive value indicating the length of the file in bytes. Minus one for errors.
 */
//*************************************************************************************************

int SemiHosting::SysFlen(unsigned long long fileHandle) {
  int rcode = -1;

  int fd = (int) fileHandle;

  struct stat st;
  fstat(fd, &st);
  rcode = st.st_size;
  
  return rcode;
}

//*************************************************************************************************
/*! \brief Returns a temporary file name.
 *
 * NOT IMPLEMENTED
 * 
 * @param[in] tmp_filename A character buffer in which to store the filename created.
 * @param[in] target_id An ID to associate with the filename created, in the range of 0 to 255.
 * @param[in] buflen The maximum number of bytes the <i>tmp_filename</i> buffer will accomodate.
 * \returns Zero if the call was successful, minus one otherwise.
 */
//*************************************************************************************************

int SemiHosting::SysTmpName(char *tmp_filename,unsigned int target_id,int buflen) {
  return -1; // not implemented...
}

//*************************************************************************************************
/*! \brief Deletes a specified file.
 *
 * NOT IMPLEMENTED
 * 
 * @param[in] src_filename The file to be deleted. A pointer to a null terminated character string.
 * \returns Zero if the file was removed successfully, minus one on error. Use <i>SysErrno</i> to
 * obtain the host error code <i>errno</i> if an error occurs.
 */
//*************************************************************************************************

int SemiHosting::SysRemove(char *src_filename) {
  return -1; // not implemented...
}

//*************************************************************************************************
/*! \brief Rename a specified file.
 *
 * NOT IMPLEMENTED
 * 
 * @param[in] old_filename The file to be renamed. A pointer to a null terminated character string.
 * @param[in] new_filename The new name for the file. A pointer to a null terminated character string.
 * \returns Zero if the file was removed successfully, minus one on error. Use <i>SysErrno</i> to
 * obtain the host error code <i>errno</i> if an error occurs.
 */
//*************************************************************************************************

int SemiHosting::SysRename(char *old_filename,char *new_filename) {
  return -1; // not implemented...
}

//*************************************************************************************************
/*! \brief Returns the number of centiseconds since the execution started.
 *
 * \returns The number of centiseconds from the start of a simulation, or minus one if an error
 * occurs. 
 */
//*************************************************************************************************

long long SemiHosting::SysClock() {
  return 0;
}

//*************************************************************************************************
/*! \brief Returns the number of seconds since 00:00 January 1, 1970.
 *
 * Returns the value from the system <i>time</i> function.
 *
 * \returns The number of seconds. 
 */
//*************************************************************************************************

unsigned long long SemiHosting::SysTime() {
  time_t curtime = time(NULL);

  return (unsigned long long) curtime;
}

//*************************************************************************************************
/*! \brief Passes a command to the host command-line interpreter.
 *
 * Allows a shell command to be executed via the system <i>system</i> function.
 *
 * @param[in] cmdline The command line to be executed. A null terminated character string.
 *
 * \returns The return status from the call.
 */
//*************************************************************************************************

int SemiHosting::SysSystem(char *cmdline) {
  return system(cmdline);
}

//*************************************************************************************************
/*! \brief Returns the value of the <b>C</b> library <i>errno</i> variable.
 *
 * Returns the <i>errno</i> value, set from some previous (semihosting) call, including: 
 *    - SysRemove
 *    - SysOpen
 *    - SysClose
 *    - SysRead
 *    - SysWrite
 *    - SysSeek
 *
 * \returns The <i>errno</i> value.
 */
//*************************************************************************************************

int SemiHosting::SysErrNo() {
  return errno; // return system errno from previous system call. value is dependent on host system...
}

//*************************************************************************************************
/*! \brief Returns the command line used to start the simulation.
 *
 * @param[out] cmdline A pointer to a character buffer in which to store the (null terminated)
 * command line string.
 *
 * \returns Zero for success, minus one otherwise.
 */
//*************************************************************************************************

int SemiHosting::SysGetCmdline(char *cmdline) {
  return -1;
}

//*************************************************************************************************
/*! \brief Returns the system stack and heap parameters.
 *
 * Return the size and extents of the heap and stack available at the time execution begins.
 *
 * @param[out] heap_base The heap base address.
 * @param[out] heap_limit The size of the heap in bytes.
 * @param[out] stack_base The stack base address.
 * @param[out] stack_limit The size of the stack in bytes.
 *
 * \returns Zero for success, minus one otherwise. 
 */
//*************************************************************************************************

int SemiHosting::SysHeapInfo(unsigned long long **heap_base,int *heap_limit,
			     unsigned long long **stack_base,int *stack_limit) {
  return -1;
}

//*************************************************************************************************
/*! \brief Returns the number of elapsed targets ticks since the execution started.
 *
 * Returns the currrent value for the simulator clock. The clock is set to zero when a simulation
 * starts, and is NOT reset otherwise. The simulator may or may not be cycle accurate, and thus the
 * value returned in entirely arbitrary.
 *
 * @param[out] elapsed_ticks Current simulator clock value.
 *
 * \returns Zero for success, minus one otherwise.
 */
//*************************************************************************************************

unsigned long long SemiHosting::SysElapsed() {
  return 0;
}

//*************************************************************************************************
/*! \brief Returns the clock tick frequency.
 *
 * The simulator clock frequency is <b>unknown</b>
 *
 * \returns Minus one always.
 */
//*************************************************************************************************

int SemiHosting::SysTickFreq() {
  return -1;
}

//*************************************************************************************************
/*! \brief Specify the system exit code.
 *
 * Use this call to set the exit code to return when the simulator exits. Typically the simulation
 * exit code will reflect user or systemic errors (such as an invalid command line option, or
 * perhaps running out of memory). The program under test, ie, the simulation itself could
 * detect some error condition (example: a self-check fail), and set the exit code for the
 * simulation. 
 *
 * @param[in] exit_code The exit code to return when the simulation exits.
 *
 * \returns Zero if this call is supported, minus one otherwise.
 */
//*************************************************************************************************

int SemiHosting::SysExit(int exit_code) {
  return -1; // when simulator is exited, use this exit_code...
}

//*************************************************************************************************
/*! \brief Checkpoint the simulation
 *
 * The <b>a64sim</b> simulation includes a simulation <i>trace</i> feature. When enabled simulation
 * <i>checkpoints</i> (register state, instruction decode info, translations) will be written to
 * a <i><trace file</i>, either at the end of every simulated instruction (when the instruction is
 * <i>retired</i>) or on demand via this call. The simulation trace mode is controlled elsewhere.
 *
 * \returns The checkpoint may or may not be created. There is no return code indicating said result.
 */
//*************************************************************************************************

void SemiHosting::SysCheckpoint() {
  // send packet to simtrace. for this to be useful need more control over sim-trace...
}

// NOTE: implement self-check assembly code subroutine as part of semihosting code.
//       document register convention. provide several (two?) subroutines, each that
//       uses a different scratch register, to allow the scratch registers themselves
//       to be checked...


//*************************************************************************************************
/*! \brief Insert code sequence to confirm a register's value.
 *
 * Insert a sequence of assembly language instructions to check the current value of a register
 * against an immediate value, setting the processor condition codes according to whether or not
 * the register value matches the immediate. A value mask is used to indicate which register bits 
 * are to checked and which are to be ignored.
 *
 * @param[in] reg_type - Register type for the register to be checked:
 *    - 0 for a general purpose register
 *    - 1 for a system register (example: SCTLR_EL1)
 * @param[in] reg_index - Register <i>index</i> for the register to be checked:
 *    - 0 thru 30 for general purpose registers X0 through X30
 *    - 31 for the <i>current</i> stack register
 *    - <i>N</i> for a system register, where <i>N</i> is formed by catenating <i>MRS/MSR</i> fields <i>op0</i>, <i>op1</i>, <i>CRn</i>, <i>CRm</i> , and <i>op2</i>.
 * @param[in] mask - Bit mask to use to indicate which bits to check.
 *
 * \returns Zero if the code sequence was inserted AND the registers value was also confirmed,
 * minus one if unable to insert the code sequence, minus two if the register in question is
 * inaccessible at the current privilege level or security state.
 */
//*************************************************************************************************

int SemiHosting::SelfCheck(int reg_type, int reg_index, unsigned long long mask) {
  return -1; // issue self-check code sequence for a single register
}

