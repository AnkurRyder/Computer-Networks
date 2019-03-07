// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h>
#include <sys/socket.h> 
#include <stdlib.h>
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8190 

int main(int argc, char const *argv[]) 
{ 
	struct sockaddr_in address; 
	int sock = 0, valread; 
	FILE* fptr;
	fptr = fopen("Test.txt","w+");
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
	char s[100]; 
	valread = read( sock , buffer, 1024);
   	printf("%s\n",buffer ); 
	scanf("%s",s);
	send(sock , s , strlen(s) , 0 );
	buffer[valread]='\0';
	fflush(stdout);

    // valread = read( sock , buffer, 1024);
    // printf("%s\n",buffer ); 

    while (1)
    {   //printf("%d\n",valread);
    	//sleep(2);
    	memset(buffer , '\0', sizeof(buffer));
        valread = read( sock , buffer, 1024);
		buffer[valread]='\0';
        printf("%s",buffer );
		valread = strlen(buffer);
		//printf("%d\n" , valread);
        fwrite(buffer, 1, valread, fptr);  
		if(valread < 1024){
        	break;
		}
    }

	 
	return 0; 
} 
