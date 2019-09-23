#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unordered_map>

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

/*
  scaffold_SAPI::PhysMemBlock *mb = my_mem.add_phys_mem();
  mb->set_address(0xffff000000000000ull);
  mb->set_size(7);
*/

  int byte_addresses  = 0;
  int hword_addresses = 0;
  int word_addresses  = 0;
  int dword_addresses = 0;
  int qword_addresses = 0;

  unordered_map<unsigned long long,int> unique_addresses;

  printf("  address             values           size   purpose   outcome  block-address         values                 free-bytes\n");
  
  unsigned long long prev_addr = 0;

  for (int i = 0; i < my_mem.phys_mem_size(); i++) {
    unsigned long long maddr = (unsigned long long) my_mem.phys_mem(i).address();
    int  count     = my_mem.phys_mem(i).size();
    bool read      = my_mem.phys_mem(i).read();
    bool init      = my_mem.phys_mem(i).do_init();
    string purpose = read ? "R" : "W";
    if (init && read) purpose = "S";

    string outcome = "-"; 
    if (read) {
      switch(my_mem.phys_mem(i).outcome()) {
        case 0:  outcome = "A"; break;
        case 1:  outcome = "P"; break;
        default: outcome = "?"; break;
      }
    }

    string mval = "";
    string mptr = my_mem.phys_mem(i).memblock();  
    for (int j = 0; j < count; j++) {
      char tbuf[128];
      sprintf(tbuf," %2.2x",(unsigned char) mptr[j]);
      mval += tbuf;
    }
    for (int j = count; j < 8; j++) {
       mval += "  .";
    }

    unsigned long long baddr = (unsigned long long) my_mem.phys_mem(i).block_address();
    string mvalb = "";
    mptr = my_mem.phys_mem(i).blockmem();  
    for (int j = 0; j < count; j++) {
      char tbuf[128];
      sprintf(tbuf," %2.2x",(unsigned char) mptr[j]);
      mvalb += tbuf;
    }
    for (int j = count; j < 8; j++) {
       mvalb += "  .";
    }
    unsigned long long freebytes = (unsigned long long) my_mem.phys_mem(i).free_bytes();

    if (maddr != prev_addr) 
      printf("\n");

    printf("0x%8.8llx   %s   %d       %s         %s       0x%8.8llx   %s   0x%8.8llx\n",maddr,mval.c_str(),count,purpose.c_str(),outcome.c_str(),baddr,mvalb.c_str(),freebytes);

    prev_addr = maddr;

    byte_addresses  += (count == 1)  ? 1 : 0;
    hword_addresses += (count == 2)  ? 1 : 0;
    word_addresses  += (count == 4)  ? 1 : 0;
    dword_addresses += (count == 8)  ? 1 : 0;
    qword_addresses += (count == 16) ? 1 : 0;

    if (unique_addresses.find(maddr) == unique_addresses.end()) {
      unique_addresses[maddr] = 1;
    } else {
      unique_addresses[maddr] += 1;
    }
  }

  printf("byte:        %d\n",byte_addresses);
  printf("half-word:   %d\n",hword_addresses);
  printf("word:        %d\n",word_addresses);
  printf("double word: %d\n",dword_addresses);
  printf("quad:        %d\n",qword_addresses);

  printf("# of unique addresses: %d\n",(int) unique_addresses.size());

  byte_addresses  = 0;
  hword_addresses = 0;
  word_addresses  = 0;
  dword_addresses = 0;
  qword_addresses = 0;

  for (unordered_map<unsigned long long,int>::iterator i = unique_addresses.begin(); i != unique_addresses.end(); i++) {
    int count = i->second;

    byte_addresses  += (count == 1)  ? 1 : 0;
    hword_addresses += (count == 2)  ? 1 : 0;
    word_addresses  += (count == 4)  ? 1 : 0;
    dword_addresses += (count == 8)  ? 1 : 0;
    qword_addresses += (count == 16) ? 1 : 0;
  }

  printf("byte:        %d\n",byte_addresses);
  printf("half-word:   %d\n",hword_addresses);
  printf("word:        %d\n",word_addresses);
  printf("double word: %d\n",dword_addresses);
  printf("quad:        %d\n",qword_addresses);
 
  return 0;
}
