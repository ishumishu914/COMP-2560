#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    int i = 0;
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Fork!");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        while (1)
        {
            i++;
            printf("i\n");
            sleep(1);
        }        
    }
    else
    {
        sleep(2);
        kill(pid, SIGSTOP);
        sleep(3);
        kill(pid, SIGCONT);
        kill(pid, SIGINT);
    }

    return 0;
}