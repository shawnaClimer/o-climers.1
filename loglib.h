#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "log.h"

extern char *program;

typedef struct list_struct {
	data_t item;
	struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

static int totalsize = 0;

int addmsg(data_t data) {
	//allocates node for data and adds to end of list
	log_t *newnode;
	int nodesize;
	nodesize = sizeof(log_t) + strlen(data.string) + 1;// + sizeof(data.time);
	totalsize = totalsize + nodesize;
	//try to add node
	if((newnode = (log_t *)(malloc(nodesize))) == NULL){
		puts("cant add node. loglib.h\n");
		return -1;
	}
	
	newnode->item.time = data.time;
	newnode->item.string = (char *)newnode + sizeof(log_t);
	strcpy(newnode->item.string, data.string);
	newnode->next = NULL;
	if (headptr == NULL){
		headptr = newnode;//list was empty
	}else{
		tailptr->next = newnode;//adds to end of list
	}
	tailptr = newnode;
	puts("added node to list\n");
	return 0;
	
}



void clearlog(void) {
	//releases storage for message and list
	//need to release memory
	headptr = NULL;
	tailptr = NULL;
	
}

char *getlog(void) {
	//writes log into a string
	//is called from savelog
	totalsize++;
	char *message = (char *)malloc(totalsize);
	//need to allocate string long enough for list
	if(message == NULL){
		puts("couldn't allocate memory in getlog\n");
		return NULL;
	}
	
	errno = 0; //set errno to 0
	message[0] = '\0'; //set message to empty
	
	long time;
	//char *tmstring;
	char *msg;
	log_t *nextnode;
	int nsize;
	
	if(headptr == NULL){
		//empty list
		perror("Empty list");
		puts("empty list");
		return NULL;
	}else{
		nextnode = headptr;
		while(nextnode != NULL){
			strcat(message, program); //begin with program name
			puts("1");
			strcat(message, ": ");
			puts("2");
			puts(message);
			time = nextnode->item.time;//read in timestamp
			nsize = sizeof(time);
			nsize++;
			//char buf[nsize + 1];
			puts("next");
			char *tmstring[nsize];
			sprintf(tmstring, "%11d", time);//convert to string
			puts(tmstring);
			strcat(message, tmstring);//add timestamp to message
			puts("3");
			msg = nextnode->item.string;//read in error msg
			strcat(message, msg);//adds to message 
			puts("4\n");
			nextnode = nextnode->next;//get next node
		}
	}
	
	
	if (errno){
		perror("Log message failed to build");
		return NULL;
	}else{
		
		return message;
	}
	
}

int savelog(char *filename){
	//save messages to file
	//use getlog to retrieve log as a string
	puts("starting savelog\n");
	char *message = getlog();
	puts(message);
	if(message != NULL){
		//first open file
		FILE *logfile;
		//open in append mode
		logfile = fopen(filename, "a");
		if (logfile == NULL){
			perror("Log file failed to open");
			puts("couldn't open file\n");
			return -1;
		}else{
			//write messages to logfile
			char ch;
			int i=0;
			while(message[i] != '\0'){
				//write to file one char at a time
				ch = message[i];
				i++;
				//checks for error while writing to file
				/*if(fputc(ch, logfile) == 'EOF'){
					//perror("Failed to write to log file");
					fclose(logfile);
					return -1;
				}*/
			}			
			//close file
			fclose(logfile);
		}
		return 0;
	}
	
}

