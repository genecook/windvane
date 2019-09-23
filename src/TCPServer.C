#include "TCPServer.h"

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

//**************************************************************************************************
//**************************************************************************************************

TCPServer::TCPServer(int portnum, bool do_block) {
    if (do_block)
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
    else
      sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    if (sockfd < 0) {
      throw std::runtime_error("ERROR opening socket");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portnum);

    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
      throw std::runtime_error("ERROR on binding");
    }

    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen);

    if (newsockfd < 0) { 
      throw std::runtime_error("ERROR on accept");
    }
}

TCPServer::~TCPServer() {
    close(sockfd);
}

//**************************************************************************************************
//**************************************************************************************************

int TCPServer::Read(unsigned char *mbuf,unsigned int size) {
    memset(mbuf,0,size);

    int numread = read(newsockfd,mbuf,size);

    if (numread < 0) { 
      throw std::runtime_error("ERROR reading from socket");
    }

    return numread;
}

//**************************************************************************************************
//**************************************************************************************************

int TCPServer::Write(unsigned char *mbuf,unsigned int size) {
    int numwritten = write(newsockfd,mbuf,size);

    if (numwritten != (int) size) {
      throw std::runtime_error("ERROR writing to socket");
    }

    return (int) size;
}

//**************************************************************************************************
//**************************************************************************************************

int TCPServer::ReadMessage(unsigned char *tbuf,unsigned int tbuf_length) {
    int delimited_size = tbuf_length + 4;

    bzero(tbuf,tbuf_length);

    unsigned char *tbuf_delimited = new unsigned char[delimited_size];

    int numread = Read(tbuf_delimited,delimited_size);

    google::protobuf::uint32 size; //<---# of bytes read - delimiter
    google::protobuf::io::ArrayInputStream ais(tbuf_delimited,4);
    google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&size);

    // the number of bytes read should be the header (4 bytes always) + the number of
    // bytes sent (as recorded in the header). check this...

    if (numread != (int)(size + 4)) {
      throw std::runtime_error("ERROR reading from socket - size expected/num bytes read mismatch");
    }

    // copy the message bytes sans header...

    memcpy(tbuf,&tbuf_delimited[4],(int) size);
    delete [] tbuf_delimited;

    // report the message length...

    return (int) size;
}

//**************************************************************************************************
//**************************************************************************************************

int TCPServer::WriteMessage(unsigned char *tbuf,unsigned int tbuf_length) {
    int delimited_size = tbuf_length + 4;

    unsigned char *tbuf_delimited = new unsigned char[delimited_size];

    google::protobuf::io::ArrayOutputStream aos(tbuf_delimited,delimited_size);
    google::protobuf::io::CodedOutputStream *coded_output = new google::protobuf::io::CodedOutputStream(&aos);
    coded_output->WriteVarint32(tbuf_length);

    memcpy(&tbuf_delimited[4],tbuf,tbuf_length);

    Write(tbuf_delimited,delimited_size);

    delete [] tbuf_delimited;

    return (int) tbuf_length;  // sans delimiter, but what caller expects...
}
