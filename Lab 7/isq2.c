// name: Ishrat Sikder
// ID: 110088181
// lab section: 53
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int fd, status;
    char* buf[3];
    buf[0] = "EXAM! EXAM! EXAM!\n";
    buf[1] = "HELP! HELP! HELP!\n";
    buf[2] = "STUDY! STUDY! STUDY!\n";

    fd = open(argv[1], O_RDWR | O_CREAT | O_EXCL);
    printf("Parent opened file: %s\n", argv[1]);

    int child1 = fork();
    int child2 = fork();

    if (child1 > 0 && child2 > 0)
    {
        printf("Parent created child process: %d\n", child1);
        printf("Parent created child process: %d\n", child2);
        wait(NULL);
        write(fd, buf[2], strlen(buf[2]));
        sleep(5);
        printf("Parent has written to file: %s\n", buf[2]);
        close(fd);
        printf("parent closed the file\n");

        
    }
    else if (child1 == 0 && child2 > 0)
    {
        write(fd, buf[0], strlen(buf[0]));
        sleep(5);
        printf("%d has written to file: %s", getpid(), buf[0]);
    }
    else if (child1 > 0 && child2 == 0)
    {
        waitpid(child1, &status, 0);
        write(fd, buf[1], strlen(buf[1]));
        sleep(5);         
        printf("%d has written to file: %s", getpid(), buf[1]);
    }
    return 0;
}