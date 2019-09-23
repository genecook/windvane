#ifndef __A64_PHYSMEM__

#include <unordered_map>
#include <vector>

#include <omp.h>

//#define DO_TRACE 1

#ifdef DO_TRACE
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "scaffold.pb.h"

#define TRACE_FILE "memtrace.pb"
#define TRACE_FILE_BLOCK "memtrace_block.pb"
#endif

#define PM_BLOCK_SIZE 32
#define PM_BLOCK_SIZE_LOG2 5
#define MEM_UNDEF_VAL 0xdc

enum { ALL_BYTES_DEFINED=0,SOME_BYTES_UNDEFINED=1,ALL_BYTES_FREE=2 };
enum { RANDOM_INITIAL_VALUE=0x100 };

//============================================================================================
// physical memory store...
//============================================================================================

enum MBLOCK_ERROR { SPLIT_ACCESS=10, MEM_ERROR=99 };

class MemBlock {
 public:
  MemBlock();
  ~MemBlock();

  void SetInitialByteValue(unsigned int _bval) { initial_byte_value = _bval; };

  int Write(unsigned long long address,unsigned char *buffer,int number_of_bytes, bool initial_values);
  int Read(unsigned long long address,unsigned char *buffer,int number_of_bytes,bool init_if_free=false);

  void ReadInitialState(unsigned long long address,unsigned char *buffer, bool is_data);

  static int Offset(unsigned long long address);
  static unsigned long long BlockAddress(unsigned long long address);
  unsigned long long FreeBytes() { return free_bytes; };
  int ByteCount();

 private:
  void ValidateAccess(int offset,unsigned char *buffer,int number_of_bytes);
  void AllocateBlock();
  void AllocateInitBlock(); 

  unsigned char InitialByteValue();

  void WriteByte(int buffer_index,unsigned char byte_val,bool is_initial_value);
  unsigned char ReadByte(int buffer_index);
  bool ByteIsFree(int buffer_index);
  unsigned char ReadFreeByte(int index);

  unsigned char *mptr;
  unsigned char *mptr_init;
  unsigned long long free_bytes;
  unsigned int initial_byte_value; // > 0xff means random value

  bool verbose;
};

class PhysicalMemory {
 public:
 PhysicalMemory();
  ~PhysicalMemory();

  void goVerbose() { verbose = true; };
  void noVerbose() { verbose = false; };

  int BlockSize() { return block_size; };

  int Write(unsigned long long address,unsigned char *buffer,int number_of_bytes,bool initial_values);
  int Read(unsigned long long address,unsigned char *buffer,bool init_if_free=false,int number_of_bytes=PM_BLOCK_SIZE);

  void ReadInitialState(unsigned long long address,unsigned char *buffer, bool is_data);

  void AddressList(vector<unsigned long long> &all_mem_addresses,bool skip_empty_blocks);

 protected:
  int BlockWrite(unsigned long long address,unsigned char *buffer,int number_of_bytes,bool initial_values);
  int BlockRead(unsigned long long address,unsigned char *buffer,bool init_if_free=false,int number_of_bytes=PM_BLOCK_SIZE);

 private:
  int block_size;
  bool verbose;
  unordered_map<unsigned long long,unsigned char> physical_memory;

  unordered_map<unsigned long long,MemBlock> physical_memory_by_block;

#ifdef DO_TRACE
  scaffold_SAPI::Memory *mt;
#endif
};

#define __A64_PHYSMEM__ 1
#endif

