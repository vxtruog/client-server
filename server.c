#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
  // các biến
  int serverSocketFd, clientSocketFd;
  struct sockaddr_in serverAddress, clientAddress;
  int clientAddressLength;
  
  // tạo socket
  serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
  if(serverSocketFd == -1)
  {
    printf("failed to create a socket\n");
    exit(1);
  }
  else
  {
    printf("socket: %d\n", serverSocketFd);
  }
  
  // liên kết
  
  // lắng nghe
  // chấp nhận
  // giao tiếp
  // đóng
  return 0;
}
