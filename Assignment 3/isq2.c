#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int status, pid;
    for (int i = 1; i < argc; i+=2)     //argv[0] is executive file so start from argv[1]
    {
        pid = fork();
        if (pid == 0)   // execute the commands in seperate child processes
            if (argc > 1)
            {
                printf("\nProcess ID = %d\n", getpid());
                execlp(argv[i], argv[i], argv[i+1], (char*)NULL);
            }            
        else if (pid > 0)
            wait(&status);
        else
            printf("Execution failed\n");    
    }
    
    return 0;
}