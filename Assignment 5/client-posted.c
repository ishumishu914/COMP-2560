#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{  
	int fd1, fd2;
	char ch;
	
	while ((fd1 = open("/tmp/myserver", O_WRONLY)) == -1)
	{  
		fprintf(stderr, "trying to connect\n");  
		sleep(1);
	}

	printf("Connected: type in data to be sent\n");  

	while((ch = getchar()) != -1) // -1 is CTRL-D
		write(fd1, &ch, 1);  

	fd2 = open("/tmp/myserver", O_RDONLY);
	while (read(fd2, &ch, 1) == 1)
	{
		fprintf(stderr, "%c", ch);
	}
	close(fd1);		
	close(fd2);
}