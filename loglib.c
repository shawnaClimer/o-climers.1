#include <stdlib.h>
#include <string.h>
#include "log.h"

typedef struct list_struct {
	data_t item;
	struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

int addmsg(data_t data) {
	//build string to add to log
	char *message[100] = buildmsg(data);
	//add msg to log
	
	return 0;
}

char *buildmsg(data_t data){
	//where msg gets assembled
	return msg;
	
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