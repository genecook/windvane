#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <strings.h>

#include <iostream>
#include <string>
#include <stdexcept>

#include "TCPClient.h"
#include "TCPServer.h"
#include "scaffold.pb.h"

#include "RSP.h"


#define MAX_MSG_LEN 8096



int main(int argc,char **argv) {

  // we are a server for gdb, but a client of the gdb-server...

  if (argc < 2) {
       fprintf(stderr,"usage %s port\n", argv[0]);
       exit(1);
  }
  
  int portno = atoi(argv[1]);

  TCPServer *server_socket;

  try {
       // we are a server for the client (gdb)...
       server_socket = new TCPServer(portno,true); // block on reads...
  } catch(const std::runtime_error& ex) {
       std::cerr << ex.what() << std::endl;
       exit(1);
  }

  
/*
  TCPServer my_server_socket(portno,true); // block on reads
  TCPServer *server_socket = &my_server_socket;
*/

  
  char *mbuf = new char[MAX_MSG_LEN + 1024];
  //char mbuf[MAX_MSG_LEN];

  
  while(true /* listening... */) {
    printf("Listening...\n");
    fflush(stdout);
    
    // get next client message...

    int num_read = 0;
    
    try {
      num_read = server_socket->Read((unsigned char *) mbuf,MAX_MSG_LEN); // Note: Read always clears mbuf
    } catch(const std::runtime_error& ex) {
       // server disconnected before client???
       std::cerr << ex.what() << std::endl;
       break;
    }

    if (num_read < 0) {
      std::cerr << "ERROR: negative packet size???" << std::endl;
      break;
    }
    
    std::cout << ">>> next client packet: '" << mbuf << "'" << std::endl;

    if (!strcmp(mbuf,"+")) {
      std::cout << "...'ack' character seen..." << std::endl;
      continue;
    }

    RSP rsp;

    std::string pdata = rsp.Decode(mbuf,num_read);
    
    std::cout << ">>>decoded: '" << pdata << "'" << std::endl;

    // send ack...

    char tbuf[4096];
    
    strcpy(tbuf,"+");
    server_socket->Write((unsigned char *) tbuf,1);

    std::cout << "...'ack' sent on received/decoded packet..." << std::endl;
    
    if (pdata.find("qSupported") != std::string::npos) {
      // send back packet size as only feature supported. hope it gets used...
      std::cout << "SUPPORTED FEATURES REQUEST..." << std::endl;
      //      sprintf(tbuf,"PacketSize=%d",MAX_MSG_LEN - 4);
      strcpy(tbuf,"");
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
    if (pdata.find("vMustReplyEmpty") != std::string::npos) {
      // send back empty packet., not sure why this is needed?
      std::cout << "MUST REPLY EMPTY REQUEST..." << std::endl;
      strcpy(tbuf,"");
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
    if (pdata.find("Hg") != std::string::npos) {
      // set thread # - okay to ignore this packet...
      std::cout << "SET THREAD NUMBER..." << std::endl;
      strcpy(tbuf,"OK");
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
    if (pdata.find("qTStatus") != std::string::npos) {
      // tracepoint - is a trace running?...
      std::cout << "TRACEPOINT: IS TRACE RUNNING NOW?..." << std::endl;
      strcpy(tbuf,"T0");  // 1 if running...
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
//    if ( (pdata.find("qTfV") != std::string::npos) || (pdata.find("qTsV") != std::string::npos) ) {
    if ( pdata.substr(0,2) == "qT") {
      // tracepoint - request data about trace state variables...
      std::cout << "TRACEPOINT: REPORT TRACE STATE VARIABLES..." << std::endl;
      //strcpy(tbuf,"l");  // QTDV there are no trace variables at startup???...
      strcpy(tbuf,""); // empty packet okay???
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }

    if (pdata.find("qfThreadInfo") != std::string::npos) {
      // tracepoint - thread info?...
      std::cout << "TRACEPOINT: START LIST OF ACTIVE THREADS..." << std::endl;
      strcpy(tbuf,"m1");  // thread 1 is 'active'...
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
    if (pdata.find("qsThreadInfo") != std::string::npos) {
      // tracepoint - thread info?...
      std::cout << "TRACEPOINT: MORE THREAD INFO - NO, SO END-LIST?..." << std::endl;
      strcpy(tbuf,"l");  // no more threads 'active'...
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
    if (pdata.find("Hc-1") != std::string::npos) {
      // set thread number...
      std::cout << "SET THREAD NUMBER: IGNORE FOR NOW (ALWAYS?)..." << std::endl;
      strcpy(tbuf,"ok");  // set thread 1 active - ignoring...
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
    if (pdata.find("qC") != std::string::npos) {
      // use previously selected thread? - ignore...
      std::cout << "USE PREVIOUSLY SELECTED THREAD: IGNORE..." << std::endl;
      strcpy(tbuf,"");  // ignoring...
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
    if (pdata.find("qAttached") != std::string::npos) {
      // did server attach to an existing process or create a new one?...
      std::cout << "DID SERVER ATTACH TO EXISTING PROCESS OR CREATE NEW ONE?..." << std::endl;
      strcpy(tbuf,"l");  // remote server attached to existing process...
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
    if (pdata.find("qOffsets") != std::string::npos) {
      // identify offsets used in relocating the sections of code to be downloaded...
      std::cout << "IDENTIFY CODE SECTION OFFSETS - BARE-METAL, SO NONE..." << std::endl;
      strcpy(tbuf,"Text=0;Data=0;Bss=0");  // no relocation is used in this target...
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
    if (pdata == "?") {
      // OOPS - gdb did not understand reply to previous query?...
      std::cout << "OOPS - GDB DID NOT UNDERSTAND RESPONSE..." << std::endl;
      strcpy(tbuf,"S05");  // stopped on TRAP exception???...
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
    if (pdata == "g") {
      // report all general register values, fl
      std::cout << "REPORT ALL GENERAL REGISTER VALUES..." << std::endl;
      strcpy(tbuf,"");
      for (int i = 0; i < 31; i++) {
	strcat(tbuf,"0000000000000000");
      }
      for (int i = 0; i < 31; i++) {
	strcat(tbuf,"00000000000000000000000000000000");
      }
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }

    
    if (pdata[0] == 'p') {
      int rindex;
      sscanf(pdata.substr(1).c_str(),"%d",&rindex);	
      std::cout << "READ REGISTER " << rindex << "..." << std::endl;
      strcpy(tbuf,"0000000000000000");
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
    if (pdata[0] == 'P') {
      int rindex;
      sscanf(pdata.substr(1).c_str(),"%x",&rindex);	
      std::cout << "WRITE REGISTER " << rindex << "..." << std::endl;
      strcpy(tbuf,"OK");
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
    //if ( (pdata == "m410ed0,8") || (pdata == "m4004a0,4") ) {
    if (pdata[0] == 'm') {
      unsigned long long maddr;
      int msize;
      sscanf(pdata.substr(1).c_str(),"%llx,%d",&maddr,&msize);	
      // read memory addr,length...
      std::cout << "READ MEMORY, ADDRESS/SIZE: 0x" << std::hex << maddr
		<< std::dec << "/" << msize << std::endl;
      strcpy(tbuf,"");  // faking memory read...
      for (int i = 0; i < msize; i++) {
	strcat(tbuf,"00");
      }
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
    if (pdata.find("vFile") != std::string::npos) {
      // file operation - will ignore...
      std::cout << "FILE OPERATION REQUEST - WILL IGNORE..." << std::endl;
      strcpy(tbuf,"");  // ignore...
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
   if (pdata.find("qSymbol::") != std::string::npos) {
      // provide symbol table info - none so far...
      std::cout << "PROVIDE SYMBOL TABLE INFO - BARE-METAL, SO NONE..." << std::endl;
      strcpy(tbuf,"OK");  // no symbol table info...
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
    if ( pdata[0] == 'Z') {
      // set software breakpoint...Z0,4004a0,4
      std::cout << "SET SOFTWARE BREAKPOINT..." << std::endl;
      unsigned long long maddr;
      int msize;
      sscanf(pdata.substr(1).c_str(),"%llx",&maddr);	
      std::cout << "BREAKPOINT ADDRESS: 0x" << std::hex << maddr << std::dec << std::endl;
      strcpy(tbuf,"OK"); // empty packet okay???
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }

   if (pdata.find("vCont") != std::string::npos) {
      // continue...
      std::cout << "CONTINUE/SW-BREAK..." << std::endl;
      strcpy(tbuf,"T 10 1:swbreak;");  // continue execution, stopped at signal thread/breakpoint...
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      continue;
    }
    
   if (pdata.find("vKill") != std::string::npos) {
      // end session...
      std::cout << "KILL SESSION..." << std::endl;
      strcpy(tbuf,"OK");  // acknowledge session end - probably not needed...
      std::string response = tbuf;
      std::string response_packet = rsp.Encode(response);
      std::cout << "response: '" << response_packet << "'" << std::endl; 
      server_socket->Write((unsigned char *) response_packet.c_str(),response_packet.size());
      break;
    }

    std::cout << "\n>>> whats the response to this packet???:";
    std::string response;
    std::cin >> response;
  }

  printf("Ending session...\n");

  delete mbuf;

  delete server_socket;

  return 0;
}
