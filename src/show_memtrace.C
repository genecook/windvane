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

using namespace std;

int main(int argc,char **argv) {
  if (argc < 2) {
    printf("No memory trace file specified.\n");
    exit(-1);
  }

  string filePath = argv[1];
 
  printf("Test a64sim memory trace, trace-file: %s!\n",argv[1]);

  scaffold_SAPI::Memory my_mem;

  fstream input(filePath,ios::in | ios::binary);

  if (!input) {
    cerr << "Can't open memory trace file '" << filePath << "'????" << endl;
    return -1;
  }

  if (!my_mem.ParseFromIstream(&input)) {
    cerr << "Can't parse memory trace file???" << endl;
    return -1;
  }

  //cout << "Physical memory trace: " << my_mem.DebugString() << endl;

  unsigned long long pc = 0xffffffffull;

  for (int i = 0; i < my_mem.phys_mem_size(); i++) {
     scaffold_SAPI::PhysMemBlock mb = my_mem.phys_mem(i);

     unsigned long long next_pc = mb.address();

     if (next_pc != pc) {
       printf("0x%016llx/0x%016llx size:%d %s init?%s 0x%016llx\n",
              (unsigned long long) mb.address(),
              (unsigned long long) mb.block_address(),
              mb.size(),(mb.read() ? "R" : "W"),
              (mb.do_init() ? "Y" : "N"),
              (unsigned long long) mb.free_bytes()
             );
       pc = next_pc;
     }
  }

  return 0;
}
