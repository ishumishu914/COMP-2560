#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

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
	int pid = fork();
	if(pid == 0)
    {
		printf("I am the child\n");  
		sleep(2);
		execlp("./donothing","donothing",NULL);
        kill(pid, SIGKILL);
	}
	else for (int i=0; i<10; i++)
    {
		//printf("I am the parent, child pid=%d\n", pid); 
        signal(SIGTSTP, sigStopHandler);
        //ctrl + c
        signal(SIGINT, sigIntHandler);         
		sleep(1);
	}
    return 0;
}