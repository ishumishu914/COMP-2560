/* student ID: 110088181
sum1= 2     sum2 = 16   sum3 = 10
L= sum2 -> signal    
S= sum1 -> pipe    
M= sum3 -> fifo
*/

#include <sys/wait.h>
#include <fcntl.h> 
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

void cp2_cHandler(int sig);
void cp2_pHandler(int sig);
void communicate(int *fd1, int *fd2);
void communicate2(int pid);
void communicate3(int pid);

int main(int argc, char const *argv[])
{
    int sum1 = 2;
    int sum2 = 16;
    int sum3 = 10;
    int cp1 = fork();
    int cp2 = fork();
    int cp3 = fork();
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);

    unlink("/tmp/sum");
	if (mkfifo("/tmp/sum", 0777) != 0)
	{
		exit(1);
	}
    int fifo = open("/tmp/sum", O_RDONLY);

    if (!cp1)
    {
        communicate(fd1, fd2);
    }
    close(fd1[0]);
    close(fd2[1]);

    if (!cp3)
    {
        communicate3(cp3);
    }

    if (!cp2)
    {
        communicate2(cp2);
    }
    signal(SIGUSR1, cp2_pHandler);

    while (1)
    {
        write(fd1[1], &sum1, 1);
        read(fd2[0], &sum1, 1);
        printf("sum1 = %d\n", sum1);

        kill(cp2, SIGUSR1);
        pause();        

        read(fifo, &sum3, 2);
        printf("sum3 = %d\n", sum3);
    }
    
    return 0;
}

void communicate(int *fd1, int *fd2)
{
    close(fd1[1]);
    close(fd2[0]);
    int sum1;// = 2;
    if(read(fd1[0], &sum1, 1) == -1)		//child read from pipe 
    { 
        perror("Read error:");
        exit(234);
    }
    sleep(1);
    write(fd2[1], &sum1, 1);
    //printf("sum1 = %d\n", sum1);
}

void communicate3(int pid)
{
    int sum3 = 10;
    int fifo = open("/tmp/sum", O_WRONLY);
    write(fifo, &sum3, 2); 
    printf("sum3 = %d\n", sum3);   
}

void communicate2(int pid)
{
	signal(SIGUSR1, cp2_cHandler);
	pause();    
}

void cp2_pHandler(int sig)
{

}

void cp2_cHandler(int sig)
{
    int status;
    int sum2 = 16;
    printf("sum3 = %d\n", sum2);
    sleep(1);
	kill(getpid(), SIGUSR1);

    wait(&status);
    if (WIFEXITED(status))
    {
        printf("child 2 terminated, status: %d\n", WEXITSTATUS(status));
    }
    if (WIFSIGNALED(status))
    {
        printf("child 2 signal %d", WTERMSIG(status));
    }
    
    
}