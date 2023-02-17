#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>  

int main()
{
	int pid, fd, i;  char c;

	if ((fd = open("fork3_test", O_RDWR | O_CREAT, 0644)) == -1 )
	{  
		perror("test");
	}

	if( (pid = fork()) < 0 )
	{
		perror("fork");  
		exit(1);
	}
	
	if(pid == 0) // child
	{
		int num =10;         
    	while(num==10)
		{
		    sleep(10);
			/*for( i = 65; i < 85; i++)
			{  
				c = i; 
				write(fd, &c ,1);
			}*/	
			close(fd);
		}
		sleep(11);
	}
	else // parent 
	{
	    sleep(2);
		/*for( i = 0 ; i< 20; i++)
		{ 
			c = 64; // character @  
			write(fd, &c ,1);
		}*/
		if (fd == -1)
		{
			write(1, "file closed\n", 13);
		}
		
	}
	
	return 0;
}

