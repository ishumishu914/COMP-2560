// reverse1.c
// solution 1: Start reading  at the end
//	Use lseek() on fileIn

#include <unistd.h> 
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]){  
	int fd1, fd2;
	char buffer; // 1 character buffer  

	long int i=0, fileSize=0;

	fd1=open(argv[1], O_RDONLY);
	fd2=open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0755);

	//two ways to figure out the size of the file

	while(read(fd1, &buffer, 1)>0)  
		fileSize++;

	printf("files size is %d\n", fileSize);

/*
	fileSize =lseek(fd1, 0, SEEK_END);
 	printf("files size is %d\n", fileSize);
	lseek(fd1, 0, SEEK_SET);
*/
	while(++i <= fileSize){  // differnce between ++i and i++
		lseek(fd1, -i, SEEK_END); 
	        read(fd1, &buffer, 1);
		write(fd2, &buffer, 1);
	}
	close(fd1);  
	close(fd2);
}
