#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <pthread.h>
#include <dirent.h> 
#define PORT 8190

struct dirent *myfile;
DIR *mydir;
void func(int* new_socket)
{
	int valread;
	char buffer[1024] = {0};
	char chunk[1024] = {0};
	char f[10000];
	memset(f,'\0',sizeof(f));
	char *hello = "Hello from Server";
	mydir = opendir(".");
	while((myfile = readdir(mydir)) != NULL)
    {
       //strcpy(t,myfile->d_name);
       strcat(f,myfile->d_name);
       char s[] = "\n";
       strcat(f,s);
        //printf(" %s\n", myfile->d_name);
    }
    closedir(mydir);
	send(*new_socket , f , strlen(f) , 0 ); 
   // printf("Hello\n");
   // fflush(stdout);
	valread = read( *new_socket , buffer, 1024); 
	printf("%s\n",buffer );
	buffer[valread]='\0';
	sleep(1); 
	
	//fflush(stdout);
	//printf("Hello message sent\n"); 

    FILE *fptr; 

	char filename[100]; 
	//read( *new_socket , buffer, 1024);
	char c;
	strcpy(filename,buffer); 

	//printf("Enter the filename to open \n"); 
	//scanf("%s", filename); 

	// Open file 
	fptr = fopen(filename, "r"); 
	if (fptr == NULL) 
	{ 
		printf("Cannot open file \n"); 
		exit(0); 
	} 

	// Read contents from file
	int len,n,m; 
	 do{
	 	//chunk[len] = '\0';
	 	n = fread(chunk, 1, sizeof(chunk), fptr);
	 	if(n){
	 		m = send(*new_socket , chunk, sizeof(chunk) , 0 );
	 	}
	 	printf("%s\n",chunk);
        	
        	//sleep(2);
	}while(n == 1024);

	fclose(fptr); 

	return;

}

int main(int argc, char const *argv[]) 
{ 
		int server_fd, valread; 
		struct sockaddr_in address; 
		int opt = 1; 
		int addrlen = sizeof(address); 
		char buffer[1024] = {0}; 
		char *hello = "Hello from server"; 
		
		// Creating socket file descriptor 
		if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
		{ 
			perror("socket failed"); 
			exit(EXIT_FAILURE); 
		} 
		
		// Forcefully attaching socket to the port 8080 
		if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
													&opt, sizeof(opt))) 
		{ 
			perror("setsockopt"); 
			exit(EXIT_FAILURE); 
		} 
		address.sin_family = AF_INET; 
		address.sin_addr.s_addr = INADDR_ANY; 
		address.sin_port = htons( PORT ); 
		
		// Forcefully attaching socket to the port 8080 
		if (bind(server_fd, (struct sockaddr *)&address, 
									sizeof(address))<0) 
		{ 
			perror("bind failed"); 
			exit(EXIT_FAILURE); 
		}
	int k = 0;
	int new_socket[3]; // Can accommodate upto 3 multiple user
	while(k < 2)
	{ 
		if (listen(server_fd, 3) < 0) 
		{ 
			perror("listen"); 
			exit(EXIT_FAILURE); 
		} 
		
		int test = (new_socket[k] = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0;

		if (test) 
		{ 
			perror("accept"); 
			exit(EXIT_FAILURE); 
		} 
		else 
		{
			pthread_t thread_id;
			pthread_create(&thread_id, NULL, (void *)&func, (void *)&new_socket[k]);
			//pthread_join(thread_id, NULL);
			//exit(0);
		}
		k++;
		printf("%d\n" , k);
	}
	pthread_exit(NULL);
	return 0; 
} 
