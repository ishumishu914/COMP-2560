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
    int fd;
    char ch;
    signal(SIGPIPE, signalHandler);

    while((fd=open("/tmp/fifo", O_WRONLY)) == -1)
    {  
        fprintf(stderr, "trying to connect\n");  
        sleep(1);
    }
    printf("Connected: type in data to be sent\n"); 

    while((ch=getchar()) != -1) // -1 is CTRL-D
    {
        write(fd, &ch, 1);  
        kill(getpid(), SIGPIPE);
    }
    
    close(fd);

    return 0;
}