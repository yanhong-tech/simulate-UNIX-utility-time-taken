
* 1. simulate UNIX utility time taken
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

double time_diff(struct timeval start_t , struct timeval end_t);

int main(int argc, char* argv[])
{
      /*
      *initialize and get START time
      */
     struct timeval start, end;
     gettimeofday(&start , NULL);

     pid_t child_pid;

     /*
     * user can enter any command to mytime.c
     */
     char *commandLineStr = (char *)NULL;

     // check need enter command for arguments
     if (argc < 2) {
       printf("Please add atleast 1 command \n");
       return 1;
     }

     commandLineStr = argv[1];
     printf("*************************************************** \n");
     printf("Command = %s\n", commandLineStr);
     printf("*************************************************** \n\n");

     /*
     * setup the arguments array for execvp
     */
     int i;
        for (i = 0; i < argc; i++) {
        argv[i] = argv[i+1];
        //printf("The command %s\n", argv[i]);
     }
     /*
     * fork a child process
     */
     child_pid = fork();
     if (child_pid < 0) { /* error occurred */
       perror("Fork Failed\n");
       return 1;
     }else if (child_pid == 0) { /* child process */
       /* call execvp in the child process and execute the commandLineStr */
       printf("*************************************************** \n");
       printf("The child process started normally. \n");
       printf("*************************************************** \n\n");
       execvp(commandLineStr, argv);
     }else{/* parent process*/
      /*parent will wait for the child to complete*/
       wait(NULL);
       printf("*************************************************** \n");
       printf("The child process Complete. \n");
       printf("*************************************************** \n\n");

     /*
     * get FINISH time
     */
     gettimeofday(&end , NULL);
     }
     /*
     * get DIFF time in microseconds
     */
     printf("*************************************************** \n");
     printf("Total time taken : %.0lf microseconds \n" , time_diff(start , end) );
     printf("*************************************************** \n\n");

     return(0);
}
/*
* get time Difference
*/
double time_diff(struct timeval start_t , struct timeval end_t)
{
    double start_ms , end_ms , diff;

    start_ms = (double)start_t.tv_sec*1000000 + (double)start_t.tv_usec;
    end_ms = (double)end_t.tv_sec*1000000 + (double)end_t.tv_usec;

    diff = (double)end_ms - (double)start_ms;

    return diff;
}
