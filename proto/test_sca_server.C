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

#define MAX_MESSAGE_LENGTH 65536

extern "C" int KickMe(void *command_buffer,void *response_buffer,int max_buffer_length);


int main(int argc, char* argv[]) {

   scaffold_SAPI::Command command;

   command.set_type(scaffold_SAPI::Command_Type_BOOT);

   unsigned char *cmdbuf = new unsigned char[MAX_MESSAGE_LENGTH];

   command.SerializeToArray(cmdbuf,MAX_MESSAGE_LENGTH); //<---this method returns pass/fail

   unsigned char *resbuf = new unsigned char[MAX_MESSAGE_LENGTH];

   if (!KickMe(cmdbuf,resbuf,MAX_MESSAGE_LENGTH)) {
     printf("OOPS!\n");
     exit(-1);
   }

   delete [] cmdbuf;

   scaffold_SAPI::Response response;

   response.ParseFromArray(resbuf,MAX_MESSAGE_LENGTH); //<---this method does NOT return pass/fail(?)

   delete [] resbuf;

   printf("Response type/status received: %d/%d, runlog: '%s'\n",
          response.type(),response.status(),response.runlog().c_str());

   return 0;
}

