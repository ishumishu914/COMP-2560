#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#define _GNU_SOURCE
#include <features.h>
#include <ctype.h>


int main(int argc, char const *argv[])
{
    for (int i = 1; i <= 64; i++)
    {
        //char *str = strdup(sys_siglist(i));
        //upper(str);
        printf("Signal #%d: %s\n" , i, strsignal(i));
        //free(str);
    }
    return 0;
}