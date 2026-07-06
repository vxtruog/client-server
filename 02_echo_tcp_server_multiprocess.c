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
	ssize_t sentBytes, receivedBytes;
	
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
	
	int opt = 1;
	setsockopt(serverSocketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
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
	if(listen(serverSocketFd, 10) == -1)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("listening...\n");
	}

  while(1)
  {
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
  
    pid_t p = fork();
    if(p == -1)
    {
      perror("fork");
      // close clientSocketFd (parent process)
      close(clientSocketFd);
      continue;
    }
    else if(p == 0)
    {
      // close serverSocketFd (child process)
      close(serverSocketFd);
  
      // comminucation
    	char buf[128];
    	char res[128];
    	while(1)
    	{
    		// receive
    		receivedBytes = recv(clientSocketFd, buf, sizeof(buf) - 1, 0);
    		if(receivedBytes == -1)
    		{
    			perror("recv");
    			break;
    		}
    		else if(receivedBytes == 0)
    		{
    			printf("client disconnected\n");
    		  break;
    		}
    		else
    		{
    			buf[receivedBytes] = '\0';
    			printf("received (%zd bytes): %s\n", receivedBytes, buf);
    		}
    		
    		// process
    		snprintf(res, sizeof(res), "%s", buf);
    		
    		// send
    		sentBytes = send(clientSocketFd, res, strlen(res), 0);
    		if(sentBytes == -1)
    		{
    			perror("send");
    			break;
    		}
    		printf("sent (%zd bytes): %s\n\n", sentBytes, res);
    	}
      
      // close clientSocketFd (child process)
      close(clientSocketFd);
      exit(EXIT_SUCCESS);
    }
    else
    {
      // close clientSocketFd (parent process)
      close(clientSocketFd);
    }  
  }

  // close serverSocketFd (parent process)
	close(serverSocketFd);
	printf("server socket closed\n");
	
	return 0;
}
