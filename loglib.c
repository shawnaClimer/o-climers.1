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
	strcat(message, program); //begin with program name
	//strcat(message, ": ");
	//add timestamp !!need to be put in a string first!! use sprintf?
	strcat(message, data.time);
	strcat(message, ": Error: nValue = ");
	//add nValue !!need to be put in a string first!!
	strcat(message, nValue);
	//add error message
	strcat(message, ermsg);
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

int main(int argc, string argv[]){
	
	//set filename for log
	char *filename = "logfile.txt";
	//add code to rename if filename command is used
	
	//program name for log file
	char *program = "./loglib: ";
	
	//integer value for log file
	int nValue = 42;
	//add code to change value if command is used
	
	//array of "error" messages
	const char *msg[3];
	msg[0] = "Happy Birthday!\n";
	msg[1] = "Thanks for visiting.\n";
	msg[2] = "That won't work.\n";
	
	//puts message and timestamp into node
	data_t temp;//for message and timestamp
	
	struct timespec res;
	clockid_t clockid;//clockid for timestamp
	clockid = CLOCK_REALTIME;
	
	for(int i=0; i<3; i++){
		clock_getres(clockid, res);
		temp.time = res.tv_nsec;
		temp.string = msg[i];
		
		addmsg(temp);
	}
	
	
	//call to savelog to write to file
	if(savelog(filename) != 0){
		perror("Failed to write to log file");
	}
	
	//call clearlog to empty list 
	clearlog();
	
	return 0;
}