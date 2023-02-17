#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    int p[2];
    char ch;
    pipe(p);
    if (pipe(p) == -1)
    {
        perror("pipe call");
		exit(1);
    }
    pid_t pid = fork();
    if (pid == 0)
    {
        close(p[0]);
        dup2(p[1], 1);  // 1 is stdout
        close(p[1]);
        execlp(argv[1], argv[1], argv[2], NULL);        
    }
    else
    {
        close(p[1]);
        int count = 0;
        int fd = open("result.txt", O_CREAT| O_RDWR | O_TRUNC, 0755);
        while (read(p[0], &ch, 1) != 0)
        {
            write(fd, &ch, 1);
            count++;
        }
        waitpid(pid, NULL, 0);
        printf("The result of %s is written to result.txt with total %d bytes\n", argv[1], count);
        close(p[0]);
    }
    
    return 0;
}