#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

void signalHandler(int sig)
{
	if (sig == SIGALRM)
	{
		printf("Ding\n");
		wait(NULL);
	}
	
}

int main(int argc, char const *argv[])
{
	signal(SIGALRM, signalHandler);
	printf("alarm application running\n");
 	int pid = fork(), sec;
	if(pid==0)
	{
		printf("waiting for alarm to go off\n");
        sscanf(argv[1], "%d", &sec);
		printf("<%d second pause>\n", sec);
		sleep(sec);
		kill(getpid(), SIGALRM);
		exit(0);
	}
	else
	{
		wait(NULL);
		printf("Done!\n");
		//sleep(1);
	}
	return 0;
}