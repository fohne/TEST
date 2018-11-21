#include <stdio.h>
#include <linux/time.h>
int main ()
{
	struct timeval __ts;
	long ts;	
	gettimeofday(&__ts, NULL);
	ts = __ts.tv_sec * 1000000 + __ts.tv_usec;

	printf("sec is %ld\n",__ts.tv_sec);
	printf("usec is %ld\n",__ts.tv_usec);
	printf("ts is  %ld\n",ts);

	/*        int edx, eax;
	asm volatile (
			"rdtsc"
			:"=a"(eax),
			 "=d"(edx)
			:
			
			);
*/
	return 0;

}
