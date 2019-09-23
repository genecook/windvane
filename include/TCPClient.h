#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include <unistd.h>

#include <strings.h>

#include <string>
#include <stdexcept>

class TCPClient {
public: 
  TCPClient(std::string hostname,int portnum, bool do_block);
  ~TCPClient();

  int Read(unsigned char *tbuf,unsigned int tbuf_length);
  int Write(unsigned char *tbuf,unsigned int tbuf_length);

  int ReadMessage(unsigned char *tbuf,unsigned int tbuf_length);
  int WriteMessage(unsigned char *tbuf,unsigned int tbuf_length);

private:
  struct sockaddr_in serv_addr;
  struct hostent *server;
  int sockfd;
};



