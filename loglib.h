#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "log.h"

typedef struct list_struct {
	data_t item;
	struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

int addmsg(data_t data) {
	//allocates node for data and adds to end of list
	log_t *newnode;
	int nodesize;
	nodesize = sizeof(log_t) + strlen(data.string) + 1;
	//try to add node
	if((newnode = (log_t *)(malloc(nodesize))) == NULL){
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
	char *message;
	//need to allocate string long enough for list
	
	errno = 0; //set errno to 0
	message[0] = '\0'; //set message to empty
	
	//get each node
	
	strcat(message, program); //begin with program name
	//add timestamp !!need to be put in a string first!! use sprintf?
	strcat(message, data.time);
	strcat(message, data.string);
	
	
	if (errno){
		perror("Log message failed to build");
		return -1;
	}else{
		
		return 0;
	}
	return message;
}

int savelog(char *filename){
	//save messages to file
	//use getlog to retrieve log as a string
	char *messages = getlog();
	if(messages != NULL){
		//first open file
		FILE *logfile;
		//open in append mode
		logfile = fopen(filename, "a");
		if (logfile == NULL){
			perror("Log file failed to open");
			return -1;
		}else{
			//write messages to logfile
			char ch;
			int i=0;
			while(messages[i] != '\0'){
				//write to file one char at a time
				ch = messages[i];
				i++;
				//checks for error while writing to file
				if(fputc(ch, logfile) == 'EOF'){
					//perror("Failed to write to log file");
					fclose(logfile);
					return -1;
				}
			}			
			//close file
			fclose(logfile);
		}
		return 0;
	}
	
}

