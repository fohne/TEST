#include <sys/time.h>
#include <stdio.h>
int main()
{
    struct timeval tp;
    struct timezon tzp;
    double start_time;

    gettimeofday(&tp, tzp);

    stime = (tp.tv_sec) + (tp_tv_usec * 1.e-6);

    int pid_pcm_memory = fork();
    
    if (pid_pcm_memory == 0) {
        //pcm_memory context
        

    } else {

        int pid_stream = fork();
        if (pid_stream == 0) {
            // stream context
            
            

        } else {
            wait();
        }
    }


    return 0;
}
