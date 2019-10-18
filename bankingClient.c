#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>
int quit = 0;
pthread_mutex_t quitLock = PTHREAD_MUTEX_INITIALIZER;
void * listenFunc(void * args){
	char buffer[300];
	int fd = *((int *) args);
	int ret =0;
	while(1){
		
		if (ret = read(fd,buffer,300) > 0){
			if (strcmp("Disconnecting from Server", buffer)==0){
				
				break;
			}
			printf("%s\n", buffer);
		}
		
	}

	
	printf("Disconnecting from Server\n");
	fflush(stdout);
	//printf("EXITING");
	pthread_mutex_lock(&quitLock);
	quit =1;
	pthread_mutex_unlock(&quitLock);
	pthread_exit(NULL);
}
int main(int argc, char const *argv[]) 
{
	    
    struct sockaddr_in address; 
    struct hostent *server;
    
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char request[300];
    char sendline[300]; 
    char recline[300]; 
    if (argc != 3){
    	write(2, "Not correct arguments",22);
    
    }
    
    int port = atoi(argv[2]);
    int i;
    
    //char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
    server = gethostbyname(argv[1]);
    if (server ==NULL){
    	write(2, "No such host", 13);
		exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
	 bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	 
    
    //memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    
    serv_addr.sin_port = htons(port); 
      /*
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   */
   while(1){
   	
   	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("Failed to connect\n");
        fflush(stdout);
        sleep(3);
        
    }else{
 			printf("Connected to server\n");
 			break;
    }
   }
   int * threadArg = (int *)malloc(sizeof(int*));
   *threadArg = sock;
   pthread_t newThread;
   pthread_attr_t newAttrStruct;
	pthread_attr_init(&newAttrStruct);
	pthread_create(&newThread, &newAttrStruct, listenFunc,(void *) threadArg);
    while(1){
		bzero(sendline, 300);
		bzero(recline, 300);
		bzero(request, 300);
		
    	fgets(request, 300, stdin);
    	request[strlen(request)-1] = '\0';
    	if (strncmp(request, "quit", 4)==0){
    		
    		
    		strcpy(sendline, "000Q");
    		//sendline = "000Q";
    		write(sock,sendline,strlen(sendline)+1);
    		sleep(2);
    		//read(sock,recline,256);
    		//printf("%s\n", recline);
    		
    		
    		
    	}
    	else if (strncmp(request, "create ", 7)==0){
    		
    		for (i=0;i<7;i++){
    			memmove(request, request+1, strlen(request));
    		}
    		/*
    		if (strlen(request < 1){
    			write(2, "Input valid Account Name", 25);
    		}
    		*/
    		char name[256];
    		strcpy(name, request);
    		name[255] = '\0';
    		char temp[300] = "C";
    		//strcat(temp,"\"");
    		strcat(temp, name);
    		//strcat(temp, "\"");
    		size_t len = strlen(temp)-1;
    		sprintf(sendline, "%03d", len);
    		//itoa(len, sendline, 256);
    		strcat(sendline, temp);
   		write(sock, sendline, strlen(sendline)+1);
			sleep(2);
    		//read(sock, recline, 256);
    		//printf("%s\n", recline);
    			
    		
    	}
    	else if (strncmp(request, "serve ", 6)==0){
    		
    		char temp[300] = "S";
    		
    		for (i=0;i<6;i++){
    			memmove(request, request+1, strlen(request));
    		}
    		strcat(temp, request);
    		size_t len = strlen(request);
    		sprintf(sendline, "%03d", len);
    		strcat(sendline, temp);
    		write(sock, sendline, strlen(sendline)+1);
    		sleep(2);
    		//accountName = request;
    		
    		
    	}
    	else if (strncmp(request, "deposit ", 8)==0){
    		
    		char temp[300] = "+";
    		//strcat(temp,"\"");
    		//strcat(temp, accountName);
    		//strcat(temp, "\"");
    		for (i=0;i<8;i++){
    			memmove(request, request+1, strlen(request));
    		}
    		strcat(temp,request);
    		
    		size_t len = strlen(request);
    		for(i=0;i<len;i++){
    			if (!(request[i] < '9') && (request[i] > '0') &&(request[i]!='.')){
    				printf("Invalid Input\n");
    				continue;
    			}
    		}
    		sprintf(sendline, "%03d", len);
    		//itoa(len, sendline, 256);
    		strcat(sendline, temp);
    		write(sock, sendline, strlen(sendline)+1);
    		sleep(2);
    		//read(sock, recline, 256);
    		//printf("%s\n", recline);
    		
    		
    	}
    	else if (strncmp(request, "withdraw ", 9)==0){
    		
    		char temp[300] = "-";
    		//strcat(temp,"\"");
    		//strcat(temp, accountName);
    		//strcat(temp, "\"");
    		for (i=0;i<9;i++){
    			memmove(request, request+1, strlen(request));
    		}
			strcat(temp,request);
   		size_t len = strlen(request);
			for(i=0;i<len;i++){
    			if (!(request[i] < '9') && (request[i] > '0') &&(request[i]!='.')){
    				printf("Invalid Input\n");
    				continue;
    			}
    		}
   		sprintf(sendline, "%03d", len);
   		//itoa(len, sendline, 256);
    		strcat(sendline, temp);
    		write(sock, sendline, strlen(sendline)+1);
    		sleep(2);
    		//read(sock, recline, 256);
    		//printf("%s\n", recline);
    		
    	}
    	else if (strncmp(request, "query", 5)==0){
    		
    		
    		
    		strcpy(sendline, "000=");
    		write(sock, sendline, strlen(sendline)+1);
    		sleep(2);
    		//read(sock, recline, 256);
   		//printf("%s\n", recline);
    		
    	}
    	else if (strncmp(request, "end", 3)==0){
    		
    		
    	
   		strcpy(sendline, "000E");
   		write(sock, sendline, strlen(sendline)+1);
    		sleep(2);
    		
    		
    	}
    	else{
    		printf("Invalid Input\n");
    	}
    	
    	pthread_mutex_lock(&quitLock);
    	if (quit==1){
    		break;
    	}
    	pthread_mutex_unlock(&quitLock);
    }
    pthread_join(newThread, NULL);
    free(threadArg);
     /*
    send(sock , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 
    */
    return 0; 
} 
