#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

// This is the server
int main(int argc, char *argv[])
{  
	int fd1, fd2;
	char ch;

	unlink("/tmp/myserver"); // delete it if it exists  
	//unlink("/tmp/myserver");

	if(mkfifo("/tmp/myserver", 0777) != 0)// || mkfifo("/tmp/server", 0777) != 0)
		exit(1);

	while (1)
	{
		fprintf(stderr, "Waiting for a client\n");  

		fd1 = open("/tmp/myserver", O_RDONLY);  
					
		fprintf(stderr, "Got a client: ");  

		while(read(fd1, &ch, 1) == 1)
		{
			fprintf(stderr, "%c", ch);
		}	
		fd2 = open("/tmp/myserver", O_WRONLY);
		write(fd2, "Message received\n", 18);

		close(fd1);
		close(fd2);
	}
}