#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{   
    //std i/o
    int count = 1; // files will naturally have at least one newline
    char c;
    FILE *fp = fopen("test.txt", "r");

    if (fp == NULL)
    {
        perror("Error! file open failed");
        //exit(1);
    }

    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '\n')        
            count++;
    }
    
    fclose(fp);
    printf("(standard i/o) test.txt has %d lines\n", count);

    return 0;
}