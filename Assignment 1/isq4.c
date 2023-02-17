#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // system i/o
    int lines = 1; // files will naturally have at least one newline
    size_t n = 0;
    char buf[BUFSIZ] = "";
    int fd = open("test.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("Error! file open failed");
        //exit(1);
    }
    while ((n = read(fd, buf,sizeof buf)) > 0)
    {
        for (int i = 0; i < n; i++)
            if (buf[i] == '\n')
                lines++;                
    }
    printf("(system i/o) test.txt has %d lines\n", lines);
    close(fd);
    
    return 0;
}
