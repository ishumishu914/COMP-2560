#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

void signalHandler(int sig)
{
    if (sig == SIGPIPE)
    {
        printf("SIGPIPE called!\n");
        wait(NULL);
    }    
}

int main(int argc, char const *argv[])
{
    int fd[2];
    pid_t pid;
    char buf[20];
    
    signal(SIGPIPE, signalHandler);

	if (pipe(fd) == -1)
    {
		perror("pipe call");
		exit(1);
	}

    switch (pid = fork())
    {
    case -1:
        perror("fork call");
        exit(2);        
        break;

    case 0:
        close(fd[0]);
        write(fd[1], "hello, hi\n", 11);
        kill(getpid(), SIGPIPE);
        break;
    
    default:
        read(fd[0], buf, 11);
        printf("%s", buf);
        wait(NULL);    
    }
    
    exit(0);
    return 0;
}