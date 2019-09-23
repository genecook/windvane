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

  if (argc < 4) {
       fprintf(stderr,"usage %s hostname client-port server-port\n", argv[0]);
       exit(1);
  }
  
  std::string server = argv[1];
  int client_portno  = atoi(argv[2]);
  int server_portno  = atoi(argv[3]);

  if (client_portno == server_portno) {
    fprintf(stderr,"client-port cannot be same as server-port. Session terminated.\n");
    exit(1);
  }

  
  TCPClient *client_socket;

  try {
       // we are a client of the server (simulator)...
    client_socket = new TCPClient(server,server_portno,false /* do NOT block on reads */);
       printf("Connected to server...\n");
  } catch(const std::runtime_error& ex) {
       std::cerr << ex.what() << std::endl;
       exit(1);
  }

  
  TCPServer *server_socket;

  try {
       // we are a server for the client (gdb)...
    server_socket = new TCPServer(client_portno,false /* do NOT block on reads */);
       printf("Listening for client...\n");
  } catch(const std::runtime_error& ex) {
       std::cerr << ex.what() << std::endl;
       exit(1);
  }

  
  unsigned char *mbuf = new unsigned char[MAX_MSG_LEN];

  // we ASSUME the client blocks until a (complete) server response is received...

  while(true /* listening... */) {
    // get next client message...

    try {
       int num_read = client_socket->Read(mbuf,MAX_MSG_LEN); // Note: Read always clears mbuf
       if (num_read > 0) {
	 
	 std::cout << ">>> we have a client request. decode and echo. send on to server..." << std::endl;
	 
         try {
	    int num_written = server_socket->Write(mbuf,num_read);
	 } catch(const std::runtime_error& ex) {
	    // problems writing to server? lets say this is bad...
            std::cerr << ex.what() << std::endl;
	    break;
	 }
	 
       }
    } catch(const std::runtime_error& ex) {
       // lets assume client disconnected...
       std::cerr << ex.what() << std::endl;
       break;
    }

    // get next server response (if any)...

    try {
       int num_read = server_socket->Read(mbuf,MAX_MSG_LEN);
       if (num_read > 0) {
	 
         std::cout << "<<< we have a server response. decode and echo. send on to client..." << std::endl;
	 
         try {
	    int num_written = client_socket->Write(mbuf,num_read);
	 } catch(const std::runtime_error& ex) {
	    // problems writing to client? lets assume client disconnected...
            std::cerr << ex.what() << std::endl;
	    break;
	 }
	 
       }
    } catch(const std::runtime_error& ex) {
       // server disconnected before client???
       std::cerr << ex.what() << std::endl;
       break;
    }
  }

  printf("Ending session...\n");

  delete server_socket;
  delete client_socket;

  delete [] mbuf;
  
  return 0;
}
