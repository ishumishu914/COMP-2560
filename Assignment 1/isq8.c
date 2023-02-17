#include <stdio.h>
#include <fcntl.h>
#include <string.h>
//#include "apue.h"

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char const *argv[])
{
    FILE *fp = fopen("file.hole", "w+");

    if (fp == NULL)
        perror("creat error");

    if (fprintf(fp, buf1, 10) != 10)
        perror("buf1 write error");

    /* offset now = 10 */

    if (fseek(fp, 16384, SEEK_SET) == -1)
        perror("fseek error");
    /* offset now = 16384 */
        
    if (fprintf(fp, buf2, 10) != 0)
        perror("buf2 write error");   
    /* offset now = 16394 */
    
    return 0;
}
