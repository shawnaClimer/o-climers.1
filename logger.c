#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "loglib.h"

int main(int argc, char **argv){
	
	//for use with getopt
	extern char *optarg;
	extern int optind;
	int c, err = 0;
	int hflag=0, nflag=0, lflag=0;
	static char usage[] = "usage: %s -h -n nValue -l filename\n";
	
	char *filename;
	int nValue;
	
	while((c = getopt(argc, argv, "hn:l:")) != -1)
		switch (c) {
			case 'h':
				hflag = 1;
				break;
			case 'n':
				nflag = 1;
				nValue = optarg;//does this need int conversion?
				break;
			case 'l':
				lflag = 1;
				filename = optarg;
				break;
			case '?':
				err = 1;
				break;
		}
	
	if(err){
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}
	//set filename for log
	if(lflag == 0){
		filename = "logfile.txt";
	}
		
	//program name for log file
	char *program = "./logger: ";
	
	//default int value for log file
	if(nflag == 0){
		nValue = 42;
	}
		
	//array of "error" messages
	const char *msg[3];
	for(int i=0; i<3; i++){
		msg[i] = ": Error: nValue = ";
		//add nValue !!need to be put in a string first!!
		strcat(msg[i], nValue);
	}
	strcat (msg[0], " - Happy Birthday!\n");
	strcat (msg[1], " - Thanks for visiting.\n");
	strcat (msg[2], " - That won't work.\n");
	
	//puts message and timestamp into node
	data_t temp;//for message and timestamp
	
	struct timespec res;
	clockid_t clockid;//clockid for timestamp
	clockid = CLOCK_REALTIME;
	
	for(int i=0; i<3; i++){
		clock_getres(clockid, res);
		temp.time = res.tv_nsec;
		temp.string = msg[i];
		
		addmsg(temp);//add message to node list
	}
	
	
	//call to savelog to write to file
	if(savelog(filename) != 0){
		perror("Failed to write to log file");
	}
	
	//call clearlog to empty list 
	clearlog();
	
	return 0;
}