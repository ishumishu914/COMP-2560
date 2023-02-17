#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    /* !! STANDARD I/O VERSION !! */
    char ch, string[100];
    FILE *fp = fopen(argv[1], "a+");

    if (fp == NULL)
    {
        perror("Error! file failed to open\n");
        exit(1);
    }
    
    //print file contents
    ch = fgetc(fp);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = fgetc(fp);
    }
    
    //append to file
    printf("\nEnter the content you wish to append:\n");
    scanf("%s", string);
    fprintf(fp, "%s", string);
    printf("\nSuccessfully written to %s\n", argv[1]);
    printf("Updated content of %s: \n", argv[1]);

    fseek(fp, 0, SEEK_SET);
    ch = fgetc(fp);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = fgetc(fp);
    }
    printf("\n");
    fclose(fp);
    return 0;
}
