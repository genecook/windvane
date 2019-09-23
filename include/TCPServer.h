#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include <unistd.h>
#include <strings.h>

#include <string>
#include <stdexcept>

class TCPServer {
public: 
  TCPServer(int portnum, bool do_block);
  ~TCPServer();

  int Read(unsigned char *tbuf,unsigned int tbuf_length);
  int Write(unsigned char *tbuf,unsigned int tbuf_length);

  int ReadMessage(unsigned char *tbuf,unsigned int tbuf_length);
  int WriteMessage(unsigned char *tbuf,unsigned int tbuf_length);

//private:
  int sockfd, newsockfd, portno, clilen;
  struct sockaddr_in serv_addr, cli_addr;
};


