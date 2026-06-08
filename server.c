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

