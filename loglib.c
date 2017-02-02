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

int addmsg(data_t data, const char *ermsg) {
	//build string to add to log
	char *message[200];
	int success = buildmsg(data, message, ermsg);
	if(success == -1){
		return -1;
	}else {
	//need to add message to list
	
		
		return 0;
	}
}

int buildmsg(data_t data, char *message, const char *ermsg){
	//where message gets assembled
	errno = 0; //set errno to 0
	message[0] = '\0'; //set message to empty
	strcat(message, program); //begin with program name
	strcat(message, ": ");
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
	
	
}

void clearlog(void) {
	
}

char *getlog(void) {
	return NULL;
}

int savelog(char *filename){
	return 0;
}

int main(int argc, string argv[]){
	
	
	return 0;
}