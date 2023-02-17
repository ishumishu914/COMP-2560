#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int *r;
    int p[2], buf[sizeof(r)];
    
    if (pipe(p) == -1)
    {
		perror("pipe call");
		exit(1);
	}

    if (fork() == 0)
    {
        close(p[0]);
        for (int i = 0; i < 5; i++)
        {
            *r = rand()%100;
            write(p[1], &r, sizeof(r));
            //write(p[1], "\t", 2);
        }
        r=0;
    }
    else
    {
        if (fork() == 0)
        {
            close(p[0]);
            for (int i = 0; i < 5; i++)
            {
                *r = rand()%100;
                write(p[1], &r, sizeof(r));
                //write(p[1], "\t", 2);
            }
            r=0;
        }
        else
        {
            close(p[1]);  
            for (int i = 0; i < 10; i++)
            {
                read(p[0], buf, sizeof(buf));
                printf("%d\n", buf);
            }
            wait(NULL);
        }        
    }
    
    return 0;
}