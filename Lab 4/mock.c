#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //printf("before fork, my parent pid is %d\n" , getpid()); 
    
    if ( fork() == 0 )
    {
        sleep(1);
        printf("Hi, I am child #1. My pid is %d and ppid is %d\n", getpid(), getppid());
    }
    else
    {
        if (fork() == 0)
        {
            sleep(2);
            printf("Hi, I am child #2. My pid is %d and ppid is %d\n", getpid(), getppid());
        }
        else
        {
            if (fork() == 0)
            {
                sleep(3);
                printf("Hi, I am child #3. My pid is %d and ppid is %d\n", getpid(), getppid());
            }
            else
            {
                sleep(4);
                printf("Hi, I am parent. My pid is %d\n", getpid());               
            }        
        }
    }

    return 0;
}