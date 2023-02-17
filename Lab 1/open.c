#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

#define PERMS 0644 // permission for open with O_CREAT
char* filename = "newfile";

int main(int arge, char * argv[])
{
	int filedes;
	
	/*Open "anotherfile" read only*/
	if ((filedes = open("filename", O_RDWR|O_CREAT, PERMS)) == -1)
	{
		printf("could not create %s/n", filename);
		exit(1);
	}
	close(filedes);
	printf("done creating file, %d \n", filedes);
	exit(0);
}

