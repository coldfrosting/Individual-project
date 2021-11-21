#include <stdio.h> // perror, printf
#include <stdlib.h> // exit, atoi
#include <unistd.h> // write, read, close
#include <arpa/inet.h> // sockaddr_in, AF_INET, SOCK_STREAM, INADDR_ANY, socket etc...
#include <string.h> // strlen


int main(int argc, char *argv[]) {

    int sockfd;
    struct sockaddr_in serveraddr;
    int len;
    char input[1000],output[1000];
 
    //create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
		perror("Socket creation failed");
		exit(-1);
	}
    else
		printf("Socket successfully created..\n");
		
	//assign IP, PORT
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("192.168.56.102");
	serveraddr.sin_port = htons(22000);
  
	//connect socket
	len = sizeof(serveraddr);
	if (connect(sockfd, (struct sockaddr *)&serveraddr, len) < 0) {
		perror("Can't connect to server");
		exit(-1);
	}
	else
		printf("Connection is successful..\n");

	//Send input and receive reply
	while(1)
	{
		printf("Send message: ");
		fgets(input, 1000, stdin);
		send(sockfd, input,strlen(input),0);
		
		len = recv(sockfd, output, 1000, 0);
		output[len] = '\0';
		printf("Server reply: %s\n", output);
	}
	
	close(sockfd);
	return 0;
}
