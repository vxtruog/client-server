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
	int socketFd;
	struct sockaddr_in serverAddress;
	ssize_t receivedBytes;

	if(argc != 3)
	{
		fprintf(stderr, "usage: %s <server_ip> <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	// create socket
	socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketFd == -1)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("socket : %d\n", socketFd);
	}
	
	// connect
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	int ret = inet_pton(AF_INET, argv[1], &serverAddress.sin_addr);
	if(ret == 0)
	{
		fprintf(stderr, "invalid IP address\n");
		exit(EXIT_FAILURE);
	}
	else if(ret == -1)
	{
		perror("inet_pton");
		exit(EXIT_FAILURE);
	}
	serverAddress.sin_port = htons(atoi(argv[2]));
	
	if(connect(socketFd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("connected\n");
	}
	
	// communication
	char buf[128];
	receivedBytes = recv(socketFd, buf, sizeof(buf) - 1, 0);
	if(receivedBytes == -1)
	{
		perror("recv");
		exit(EXIT_FAILURE);
	}
	else if(receivedBytes == 0)
	{
		printf("server disconnected\n");
	}
	else
	{
		buf[receivedBytes] = '\0';
		printf("received %zd bytes\n", receivedBytes);
		printf("received : %s\n", buf);
	}
	
	// close
	close(socketFd);
	printf("socket closed\n");

	return 0;
}
