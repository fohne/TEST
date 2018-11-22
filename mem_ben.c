#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>


#define DEBUG_ON_
#ifdef DEBUG_ON
#define DEBUG(format, args...) \
	printf("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
	#define DEBUG(format, args...)
#endif

#define KIB 1000
#define MIB KIB*1000
#define _100MIB MIB*100
#define SECOND_U 1*1000*1000
        static unsigned char arrayA[_100MIB] ;
        static unsigned char arrayB[_100MIB] ;
int main (int argc, char** argv)
{
	struct timeval synctime;
	long timeStamp = 0;
        unsigned long int memory_sz = _100MIB;

	if (argc > 1) {
		char* parser;
		do {
			DEBUG("The number of arguments is %d \n", argc);
			argv++;
			argc--;

			if (strncmp(*argv, "-ts",3) == 0 ||
		    	    strncmp(*argv, "/ts",3) == 0	    
		   	) {
				parser = strchr(*argv, '=');
				parser++;
				timeStamp = atol(parser);

                                timeStamp += 2 * SECOND_U;
			}

                        if (strncmp(*argv, "-sz", 3) == 0 ||
                            strncmp(*argv, "/sz", 3) == 0 
                        ) {
                                parser = strchr(*argv, '=');
                                parser++; 
                                memory_sz = atoi(parser);
                               if (strstr(parser,"MB") || 
                                   strstr(parser, "mb")
                               ) 
                                        memory_sz *= 1000000;
                               if (strstr(parser, "GB") ||
                                   strstr(parser, "gb")
                               )
                                        memory_sz *= 1000000000;
                               if (memory_sz > 2000000000)
                                        memory_sz = 2000000000;
                               if (memory_sz < 32*1024*1024)
                                        memory_sz = _100MIB;
printf("%d\n",memory_sz);
                        }
                        
	
		} while (argc > 1);
        }

	struct timeval check_ts;
	gettimeofday(&check_ts, NULL);

	if ((timeStamp + 10 * SECOND_U) < (check_ts.tv_sec * SECOND_U))
		timeStamp = check_ts.tv_sec * SECOND_U + check_ts.tv_usec;
        
        for (int i = 0; i < _100MIB; i++)
        {
                arrayA[i] = 1;
	        arrayB[i] = 0;
        }

	do {
                int j = 1;
                DEBUG("timestamp is %ld\n",timeStamp);

		for (int i = 0; i < _100MIB; i++) {

		        arrayA[i] = j;
		}

                j = j * 9 / (j * 10 + 1) + j; 

	        long stoptime = timeStamp + SECOND_U;
                while (timeStamp < stoptime) {
	
	                gettimeofday(&synctime, NULL);
                        timeStamp = synctime.tv_sec * SECOND_U + synctime.tv_usec;
                } 

		timeStamp = stoptime;

	} while(1);


	return 0; 


}
