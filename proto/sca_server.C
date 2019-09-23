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


void KickMe(string *command,string *response_str);


int main(int argc, char* argv[]) {

   scaffold_SAPI::Command command;

   command.set_type(scaffold_SAPI::Command_Type_BOOT);

   string command_str;

   command.SerializeToString(&command_str);

   string response_str;
   KickMe(&command_str,&response_str);

   scaffold_SAPI::Response response;

   response.ParseFromString(response_str);

   printf("Response type/status received: %d/%d, runlog: '%s'\n",
          response.type(),response.status(),response.runlog().c_str());

   return 0;
}


void KickMe(string *command_str,string *response_str) {

   scaffold_SAPI::Command command;

   command.ParseFromString(*command_str);

   printf("Command index: %d\n",command.type());

   scaffold_SAPI::Response response;

   response.set_type(command.type());
   response.set_status(-1);
   response.set_runlog("Simulator booted.");
   response.set_errlog("");
   response.set_tracelog("");

   printf("Response type/status sent: %d/%d, runlog: '%s'\n",
          response.type(),response.status(),response.runlog().c_str());

   response.SerializeToString(response_str);
}
