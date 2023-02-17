#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigIntHandler(int sig)
{
    printf("\n%d: SIGINT Handler function\n", sig);
}

void sigQuitHandler(int sig)
{
    printf("\n%d: SIGQUIT Handler function\n", sig);
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 7; i++)
    {
        signal(SIGINT, sigIntHandler);
        sleep(1);

        signal(SIGQUIT, sigQuitHandler);
        sleep(1);        
    }

    return 0;
}