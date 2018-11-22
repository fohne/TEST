#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>


#define DEBUG_ON
#ifdef DEBUG_ON
#define DEBUG(format, args...) \
	printf("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
	#define DEBUG(format, args...)
#endif

#define KIB 1024
#define MIB KIB*1024
#define _100MIB 100*MIB
#define SECOND_U 1*1000*1000
int main (int argc, char** argv)
{
	struct timeval synctime;
	long timeStamp = 0;


	if (argc > 1) 
		
		do {
			DEBUG("The number of arguments is %d \n", argc);
			argv++;
			argc--;
			if (strncmp(*argv, "-ts",3) == 0 ||
		    	strncmp(*argv, "/ts",3) == 0	    
		   	) {
				char* parser = strchr(*argv,'=');
				DEBUG("%s\n",*argv);
				parser++;
				DEBUG("%s\n",parser);
				timeStamp = atol(parser);
				DEBUG("timestamp is %ld\n",timeStamp);

                                timeStamp += 2 * SECOND_U;
			}
	
		} while (argc > 1);

	struct timeval check_ts;
	gettimeofday(&check_ts, NULL);

	if ((timeStamp + 10 * SECOND_U) < (check_ts.tv_sec * SECOND_U))
		timeStamp = check_ts.tv_sec * SECOND_U + check_ts.tv_usec;
	unsigned char arrayA[_100MIB] ;
	unsigned char arrayB[_100MIB] ;
        for (int i = 0; i < _100MIB; i++)
        {
                arrayA[i] = 1;
	        arrayB[i] = 0;
        }

	do {
                DEBUG("timestamp is %ld\n",timeStamp);
		for (int i = 0; i < _100MIB; i++) {
		        arrayB[i] = arrayA[i];
		}
	        long stoptime = timeStamp + SECOND_U;
                while (timeStamp < stoptime) {
	
	                gettimeofday(&synctime, NULL);
                        timeStamp = synctime.tv_sec * SECOND_U + synctime.tv_usec;
                } 

		timeStamp = stoptime;

	} while(1);


	return 0; 


}
