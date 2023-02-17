#include <unistd.h>
#include <fcntl.h>	
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int n;
    //char buffer[100];
    char c;
    int fd = open(argv[1], O_RDONLY);

    if (argc == 1)
    {
        printf("No files passed!"); 
    }
    else
    {
        if (fd == -1)
        {
            printf("Error opening %s, exiting\n", argv[1]);
            exit(0);
        }        
    }

    while( (read(fd, &c, 1)) > 0)
    {
        printf("%c", c);        
    }  

    close(fd);
    exit(0);
    
    return 0;
}