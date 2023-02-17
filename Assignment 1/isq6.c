#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    /* !! SYSTEM I/O VERSION !! */

    // open file    
    int fd = open(argv[1], O_RDWR | O_APPEND); //replace filename with argv[1]
    char ch, string[100];

    if (fd == -1)
    {
        perror("Error! file failed to open\n");
        //exit(1);
    }
    
    //read contents from file & print
    while (read(fd, &ch, 1) > 0)
    {
        printf("%c", ch);    
    }
    
    //append to file
    printf("\nEnter the content you wish to append:\n");
    scanf("%s", string);
    if (write(fd, string, strlen(string)) < 0)
    {
        perror("Problem in writing to file\n");
    }
    printf("\nSuccessfully written to %s\n", argv[1]);
    printf("Updated content of %s: \n", argv[1]);
    
    // print updated file content
    lseek(fd, 0, SEEK_SET);
    while (read(fd, &ch, 1) > 0)
    {
        //printf("%c", ch);
        write(1, &ch, 1);    
    }
    printf("\n");
    close(fd);

    return 0;
}