 #ifndef _INTERFACE
#define _INTERFACE

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <float.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/time.h>

typedef struct account account;
struct account {
	char accountName[256];
	double currentBalance;
	int inSessionFlag;
};
void end(char * accName);
 typedef struct node node;
struct node{
	account* data;
	node* nextNode;
};

typedef struct helperArgs helperArgs;
struct helperArgs{
  char* buf;
  int newfd;

};
struct fdList{
	int name;
	struct fdList * next;
};


//bankingServer functions

void printDiagnostics();
void create(char* accName, int newsockfd);
void serve(char* accName, int newsockfd);
void deposit(char* accName, double depositAmount); 
void withdraw(char* accName, double withdrawAmount, int newsockfd); 
double query(char* accName);
void* helper(void* args); 
void intHandler(int dummy);
//LINKED LIST FUNCTIONS
node* getHead();
account* getAccount(char* accName);
void createList(account* newAccount); //Check if list already exists
void addAccount(account* newAccount);


#endif 
