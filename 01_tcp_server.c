#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
  // variables
  int serverSocketFd, clientSocketFd;
  struct sockaddr_in serverAddress, clientAddress;
  socklen_t clientAddressLength = sizeof(clientAddress);
  ssize_t sentBytes;

  if(argc != 2)
  {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  // create socket
  serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
  if(serverSocketFd == -1)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("socket: %d\n", serverSocketFd);
  }
  
  // bind
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_port = htons(atoi(argv[1]));
  if(bind(serverSocketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
  {
    perror("bind");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("bound\n");
  }
  
  // listen
  if(listen(serverSocketFd, 1) == -1)
  {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("listening...\n");
  }
  
  // accept
  memset(&clientAddress, 0, sizeof(clientAddress));
  clientSocketFd = accept(serverSocketFd, (struct sockaddr *)&clientAddress, &clientAddressLength);
  if(clientSocketFd == -1)
  {
    perror("accept");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("accepted\n");
  }
  
  // comminucation
  const char *msg = "hello, i'm Vu Xuan Truong.";
  sentBytes = send(clientSocketFd, msg, strlen(msg), 0);
  if(sentBytes == -1)
  {
    perror("send");
    exit(EXIT_FAILURE);
  }
  printf("sent %zd bytes\n", sentBytes);
  printf("message: \"%s\"\n", msg);
  
  // close
  close(clientSocketFd);
  printf("client socket closed\n");
  close(serverSocketFd);
  printf("server socket closed\n");
  
  return 0;
}
