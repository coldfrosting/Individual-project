#include <stdio.h> // perror, printf
#include <stdlib.h> // exit, atoi
#include <unistd.h> // read, write, close
#include <arpa/inet.h> // sockaddr_in, AF_INET, SOCK_STREAM, INADDR_ANY, socket etc...
#include <string.h> // memset
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, client;
	int len, data_len;
	char data[1000];
	 
	//Create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("Socket creation failed");
		exit(-1);
	}
	 else
		printf("Socket successfully created..\n");
		
	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(22000);
	
	//Bind socket
	len = sizeof(servaddr);
	if (bind(sockfd, (struct sockaddr *)&servaddr, len) < 0) {
		perror("Bind failed");
		exit(-1);
	}
	else
		printf("Binding socket successful..\n");
		
	//Listen
	if (listen(sockfd, 2) < 0) {
		perror("Listen error");
		exit(-1);
	}
	else
		printf("Server listening..\n");
		
	//Accept data
	while (1) {
		len = sizeof(client);
		printf("Waiting for incoming connections...\n");
		
		if ((connfd = accept(sockfd, (struct sockaddr *)&client, &len)) < 0) {
		  perror("accept error");
		  exit(-1);
		}
		else
			printf("Server accept the client...\n");
			
		char *ip_client = inet_ntoa(client.sin_addr);
		printf("Accepted new connection from client %s:%d\n", ip_client, ntohs(client.sin_port));
    
	//Read and echo data
		data_len = 1;
		while(data_len)
		{
			data_len = recv(connfd, data, 1000, 0);
			if(data_len)
			{
				send(connfd, data, data_len, 0);
				data[data_len] = '\0';
				printf("Echo back: %s",data);
			}
		}
		printf("Client disconnected! \n\n");
		close(connfd);
	}
	close(sockfd);
	return 0;
}
