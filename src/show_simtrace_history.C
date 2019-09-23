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
 
  printf("Test a64sim sim trace, summary trace-file: %s!\n",argv[1]);

  scaffold_SAPI::TraceHistory my_trsum;

  fstream input(filePath,ios::in | ios::binary);

  if (!input) {
    cerr << "Can't open sim-trace file '" << filePath << "'????" << endl;
    return -1;
  }

  if (!my_trsum.ParseFromIstream(&input)) {
    cerr << "Can't parse sim-trace summary file???" << endl;
    return -1;
  }

  cout << "SimTrace summary: " << my_trsum.DebugString() << endl;

  return 0;
}
