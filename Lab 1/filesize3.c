#include <stdio.h>

int main(int argc, char *argv[]){  
	FILE *fd;
	
	int ch;

	int fileSize=-1;

	fd = fopen(argv[1], "r+");      

	do
	{
		ch=getc(fd);  //printf("ch=%c ", ch);
		fileSize++;
		printf("fileSize=%d\n", fileSize);
	} while( ch != EOF);
	
	printf("Size of %s is %d\n", argv[1], fileSize);
}

