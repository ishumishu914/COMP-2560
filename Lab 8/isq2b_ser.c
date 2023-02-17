#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    int fd;
    char ch;
    char buf[20];

    unlink("/tmp/fifo");
	if (mkfifo("/tmp/fifo", 0777) != 0 )
    {
		/*if (errno != EEXIST) 
        {
			perror("receiver: mkfifo");
			exit(4);
		}*/
        exit(1);
	}
    //while(1)
    //{
        fprintf(stderr, "waiting for client\n");
        fd = open("/tmp/fifo", O_RDONLY);
        fprintf(stderr, "got a client: ");

        while(read(fd, &ch, 1) == 1)
            fprintf(stderr, "%c", ch);       
    //}
    
    //close(fd);
    return 0;
}