#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#include "a64sim_interface.h"
#include "scaffold.pb.h"

using namespace std;

#define MAX_BUFFER_LENGTH 4096

void show_result(void *response_buffer,int len) {
   scaffold_SAPI::Response response;

   response.ParseFromArray(response_buffer,len);
   
   if (response.status() == 0) {
     printf("%s",response.tracelog().c_str());
   } else {
     printf("Response: type: %d status: %d\n",response.type(),response.status());
     printf("          runlog-entry: '%s'\nerrlog-entry: '%s'\ntracelog-entry: '%s'\ndebuglog-entry: '%s'\n",
            response.runlog().c_str(),response.errlog().c_str(),response.tracelog().c_str(),response.debuglog().c_str());
   }
}

int main(int argc,char **argv) {
  printf("#Test serial simulator interface!\n");

  int num_instrs = 1000;

  if (argc > 1) sscanf(argv[1],"%u",&num_instrs);

  printf("# of instructions = %d\n",num_instrs);

  char request_buffer[MAX_BUFFER_LENGTH], response_buffer[MAX_BUFFER_LENGTH];

  scaffold_SAPI::Command request;

  int response_buffer_length = 0;

  printf("#BOOT SIMULATOR...\n");

  request.set_type(scaffold_SAPI::Command_Type_BOOT);
  request.SerializeToArray(request_buffer,request.ByteSize());

  SimulatorQuery(request_buffer,request.ByteSize(),response_buffer,&response_buffer_length);
  show_result(response_buffer,response_buffer_length);


  printf("#INITIALIZE SIMULATOR...\n");

  request.set_type(scaffold_SAPI::Command_Type_INIT);
  request.SerializeToArray(request_buffer,request.ByteSize());

  SimulatorQuery(request_buffer,request.ByteSize(),response_buffer,&response_buffer_length);
  show_result(response_buffer,response_buffer_length);


  printf("\n#SETUP FOR FREERUN...\n");

  request.set_type(scaffold_SAPI::Command_Type_INIT_FREERUN);
  request.set_cpuid(0);
  request.set_count(1);
  request.set_seed(time(NULL));
  request.set_verbose(0);
  request.SerializeToArray(request_buffer,request.ByteSize());

  SimulatorQuery(request_buffer,request.ByteSize(),response_buffer,&response_buffer_length);
  show_result(response_buffer,response_buffer_length);
  

  printf("\n#STEPPING...\n");

  request.set_type(scaffold_SAPI::Command_Type_FREERUN_STEP);

  for (int i = 0; i < num_instrs; i++) {
     request.set_step_index(i);
     request.SerializeToArray(request_buffer,request.ByteSize());
     SimulatorQuery(request_buffer,request.ByteSize(),response_buffer,&response_buffer_length);
     show_result(response_buffer,response_buffer_length);
  }

  printf("#POWER DOWN SIMULATOR...\n");

  request.set_type(scaffold_SAPI::Command_Type_POWER_DOWN);
  request.set_cpuid(0);
  request.SerializeToArray(request_buffer,request.ByteSize());

  SimulatorQuery(request_buffer,request.ByteSize(),response_buffer,&response_buffer_length);
  show_result(response_buffer,response_buffer_length);


  exit(0);
}

