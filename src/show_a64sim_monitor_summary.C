#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <strings.h>

#include <iostream>
#include <string>
#include <stdexcept>

#include "TCPClient.h"
#include "scaffold.pb.h"
#include "a64sim.h"

using namespace std;

bool verbose;

#define MAX_BUF_LEN 4096

string GetMessage(TCPClient *client_socket) {
      int n = 0;
      unsigned char tbuf[MAX_BUF_LEN];

      try {
        n = client_socket->Read(tbuf,MAX_BUF_LEN);
      } 
      catch(const std::runtime_error& ex ) {
        std::cerr << ex.what() << std::endl;
        delete client_socket;
        exit(1);       
      }

      if ( (n <= 0)  || (strlen((const char *) tbuf) <= 0) ) {
        std::cerr << "ERROR: zero length response received. Probable cause: server has been terminated." << std::endl;
        delete client_socket;
        exit(1);       
      }

      string msg_str;
      msg_str.append((const char *) tbuf,n);

      // send acknowledge...

      try {
	n = client_socket->Write((unsigned char *) "\n",1);
      } 
      catch(const std::runtime_error& ex ) {
        std::cerr << ex.what() << std::endl;
        delete client_socket;
        exit(1);       
      }

      return msg_str;
}

int GetMessageType(TCPClient *client_socket) {
  scaffold_SAPI::Command my_cmd;

  my_cmd.ParseFromString(GetMessage(client_socket));

  return (int) my_cmd.type();
}

void GetCpuStateMessage(TCPClient *client_socket) {
  scaffold_SAPI::CpuSlice state;

  state.ParseFromString(GetMessage(client_socket)); 

  if (verbose)
    cout << "CPU state: " << state.DebugString() << endl;
}

void GetMemoryAccessMessage(TCPClient *client_socket) {
  scaffold_SAPI::MemoryAccessDebug ma;

  ma.ParseFromString(GetMessage(client_socket));

  if (verbose)
    cout << "Memory Access: " << ma.DebugString() << endl;
}

void GetPacketMessage(TCPClient *client_socket) {
  scaffold_SAPI::Packet pkt;

  pkt.ParseFromString(GetMessage(client_socket));

  if (verbose)
    cout << "Packet: " << pkt.DebugString() << endl;
  else if (pkt.state() == RETIRE_STATE) {
    // show disassembly...
    printf("0x%8.8llx  %s",(unsigned long long) pkt.pc(),pkt.disassembly().c_str());
  }
}

int main(int argc, char *argv[]) {
    verbose = false;

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    int portno = atoi(argv[2]);
    string server = argv[1];
    TCPClient *client_socket;

    try {
      client_socket = new TCPClient(server,portno,false);
    } 
    catch(const std::runtime_error& ex ) {
       std::cerr << ex.what() << std::endl;
       exit(1);       
    }

    if (verbose)
      printf("Connected to sim server...\n");

    bool listening = true;

    while(listening) {
      int message_type = GetMessageType(client_socket);

      switch(message_type) {
        case 0:  if (verbose) printf("BOOT...\n");                  
                 break;
        case 1:  if (verbose) printf("INITIAL CPU STATE...\n");     
	         GetCpuStateMessage(client_socket);
                 break;
        case 2:  if (verbose) printf("FINAL STATE...\n");           
	         GetCpuStateMessage(client_socket);
                 break;
        case 3:  if (verbose) printf("WRITE PHYSICAL MEMORY...\n"); 
	         GetMemoryAccessMessage(client_socket);
                 break;
        case 4:  if (verbose) printf("READ PHYSICAL MEMORY...\n");  
	         GetMemoryAccessMessage(client_socket);
                 break;
        case 5:  if (verbose) printf("STEP CPU...\n");              
	         GetCpuStateMessage(client_socket);
                 break;
        case 6:  if (verbose) printf("STEP PACKET...\n");           
	         GetPacketMessage(client_socket);
                 break;
        case 7:  if (verbose) printf("HANGUP...\n");                
	         listening = false;
                 break;
        default: if (verbose) printf("UNKNOWN cmd received...\n");
                 delete client_socket;
                 exit(1);
	         break;
      }

      //std::cout << "hit return to continue...";
      //string ts;
      //getline(cin,ts);
    }

    if (verbose) 
       printf("Normal client end...\n");

    delete client_socket;

    return 0;
}
