#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "loglib.h"

char *program;

	
int main(int argc, char **argv){
	//program name for log file
	program = argv[0];
	
	//for use with getopt
	extern char *optarg;
	extern int optind;
	int c, err = 0;
	int hflag=0, nflag=0, lflag=0;
	static char usage[] = "usage: %s -h -n nValue -l filename\n";
	
	char *filename;
	char *n;
	int nValue;
	
	while((c = getopt(argc, argv, "hn:l:")) != -1)
		switch (c) {
			case 'h':
				hflag = 1;
				break;
			case 'n':
				nflag = 1;
				n = optarg;
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
	//set default filename for log
	if(lflag == 0){
		filename = "logfile.txt";
	}
	if(hflag ==1){
		puts("-h for help\n-l filename to name output file\n-n x to enter an integer\n");
	
	}	
	
	//default int value for log file
	if(nflag == 0){
		n = "42";
	}//else
		//nValue = atoi(n);
	//
	data_t temp;//for message and timestamp
	
	struct timespec res;
	struct timespec tp;
	clockid_t clockid;//clockid for timestamp
	clockid = CLOCK_REALTIME;
	
	// "error" messages
	char *msg = (char *)malloc(200);
	if(msg == NULL){
		perror("Couldn't allocate memory");
		return -1;
	}
	int i;
	
	for(i=0; i<3; i++){
		msg[0]='\0';//empty string
		strcpy(msg, ": Error: nValue = ");
		strcat(msg, n);
		if(i==0){
			strcat(msg, " - No shoes\n");
			//puts("first message");
		}else if(i==1){
			strcat(msg, " - No shirt\n");
		}else{
			strcat(msg, " - No service.\n");
			//puts("third message");
		}
		if(clock_getres(clockid, &res) == 0){
			//get the time
			if(clock_gettime(clockid, &tp) == 0){
				temp.time = tp.tv_nsec;//time in nanosecs
			}
		}
		
		temp.string = msg;
		//add message to node list
		if(addmsg(temp) == -1){
			//puts("did not add node to list");
			perror("node did not get added to list");
			return -1;
		}
		
	}
	
	
	//call to savelog to write to file
	if(savelog(filename) != 0){
		perror("Failed to write to log file");
		return -1;
	}
	
	//call clearlog to empty list 
	clearlog();
	
	
	
	
	
	return 0;
}