// Client side C/C++ program to demonstrate multiple client server program 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <pthread.h>
#define PORT 8888 

void func(int sock)
{
	char redbuff[1024];
	int a;
	while(1)
	{
		a = read(sock , redbuff , 1024);
		redbuff[a] = NULL;
		if(a > 0)
			printf("%s\n" , redbuff);
	}
}

int main() 
{ 
	struct sockaddr_in address; 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char *hello = "Hello from client"; 
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	memset(&serv_addr, '0', sizeof(serv_addr)); 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	}
	printf("Hello message sent\n");
	send(sock , hello , strlen(hello) , 0);
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, (void *)&func, sock);
	while(1){ 
		scanf("%[^\n]%*c" , buffer);
		send(sock , buffer , strlen(buffer) , 0 ); 
	} 
	pthread_exit(NULL); 
	return 0; 
} 

