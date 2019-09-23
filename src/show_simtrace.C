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
    printf("No sim-trace file specified.\n");
    exit(-1);
  }

  string filePath = argv[1];
 
  printf("Test a64sim sim trace, trace-file: %s!\n",argv[1]);

  scaffold_SAPI::Scaffold my_scaffold;

  fstream input(filePath,ios::in | ios::binary);

  if (!input) {
    cerr << "Can't open sim-trace file '" << filePath << "'????" << endl;
    return -1;
  }

  if (!my_scaffold.ParseFromIstream(&input)) {
    cerr << "Can't parse sim-trace???" << endl;
    return -1;
  }

  cout << "SimTrace: " << my_scaffold.DebugString() << endl;

/*
  scaffold_SAPI::Cpu my_core = my_scaffold.core(0);

  printf("# of translations: %d\n",(int) my_core.translations_size());
 
  for (int i = 0; i < (int) my_core.translations_size(); i++) {
    printf("%05d 0x%08llx/0x%08llx %d %d\n", i, (unsigned long long) my_core.translations(i).la(), 
           (unsigned long long) my_core.translations(i).pa(),
	   (int) my_core.translations(i).is_data(),(int) my_core.translations(i).is_write());
  }
*/
  
  return 0;
}
