// a stream socket server demo

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT "3490"  // cổng mà người dùng kết nối đến
#define BACKLOG 10   // số kết nối đang chờ xử lý tối đa trong hàng đợi

void sigchld_handler(int s)
{
  void(s);                    // tránh cảnh báo biến không được sử dụng
  int saved_errno = errno;    // waitpid() có thể ghi đè nên errno, nên chúng ta sẽ lưu trữ và phục hồi nó sau
  while(waitpid(-1, NULL, WNOHANG) > 0);
  errno = saved_errno;
}

void *get_in_addr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET)
  {
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}




      
