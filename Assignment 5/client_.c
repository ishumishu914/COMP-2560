#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){  
	int fd;
	char ch;
	
	while((fd=open("../myserver", O_WRONLY))==-1){  
		fprintf(stderr, "trying to connect\n");  
		sleep(1);
	}

	printf("Connected: type in data to be sent\n");  

	while((ch=getchar()) != -1) // -1 is CTRL-D
		write(fd, &ch, 1);  
	close(fd);
}

