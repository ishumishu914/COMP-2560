#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#define _GNU_SOURCE

void sigIntHandler(int sig)
{
    signal(SIGINT, sigIntHandler);
    printf("\tCtrl + c pressed!\n");
    fflush(stdout);
}

void sigStopHandler(int sig)
{
    signal(SIGTSTP, sigStopHandler);
    printf("\tCtrl + Z ignored!\n");
}

int main(int argc, char const *argv[])
{
    /*signal(SIGTSTP, sigStopHandler);
    //ctrl + c
    signal(SIGINT, sigIntHandler);
    while (1)
    {}*/

    pid_t pid = fork();
    if (pid < 0)
    {
        printf("error\n");
        exit(EXIT_FAILURE);  
    }
    if (pid == 0)
    {
        char *args[] = {"./donothing", NULL};
        execvp(args[0], args);
    }
    else
    {
        for (int i = 0; i < 15; ++i)
        {
            printf("I am in parent process.\n");
            //send a signal to child
            kill(pid, SIGKILL);
            sleep(1);
        }
    }
    
    return 0;
}