#include <unistd.h>		//for lseek 
#include <stdio.h>		
#include <fcntl.h>	

int main(int argc, char const *argv[])
{
    int fd = open("test.txt", O_RDONLY);
    int size = lseek(fd, 0, SEEK_END);
    printf("test.txt filesize is %d\n", size);
    close(fd);
    
    return 0;
}