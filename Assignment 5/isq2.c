#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

void player(char *s, int *fd1);
//void player2(int pid);
//void parent_sigHandler(int sig); 

int main(int argc, char *argv[])
{
	char turn = 'T';
	
	unlink("/tmp/fifo");
	if (mkfifo("/tmp/fifo", 0777) != 0)
	{
		exit(1);
	}
	int fifo = open("/tmp/fifo", O_RDONLY);
	int fifo2 = open("/tmp/fifo", O_WRONLY);
	printf("This is a 2-player game with a referee\n");  

	//identify parent code, child code
	if(!fork())  //one child process for player TOTO
		player("TOTO", fifo2);


   //-------------------------------------------------------------------
	int pid = fork();
	if(!fork())
		player("TITI", fifo2);
	

	while(1)
	{
		printf("\nReferee: TOTO plays\n\n");  
		write(fifo2, &turn, 1);  //parent write to pipe 1, fd1
		//	printf("TOTO Step 1\n");  // added by me

		read(fifo,  &turn, 1);
		//	printf("TOTO Step 4\n"); //added by me

		printf("\nReferee: TITI plays\n\n");  
	}
}

void player(char *s, int *fd1)
{  
	int points=0;
	int dice;
	long int ss=0;  
	char turn;  
	//int fifo = open("/tmp/fifo", O_WRONLY);

	while(1)
	{
		int ret = read(fd1, &turn, 1);   //child read from pipe1 ,ie fd1
	//	printf("TOTO Step 2\n");  // added		
		if(ret == -1)
		{
			perror("Read error:");
			exit(234);
		}

		printf("%s: playing my dice\n", s);  
		dice = (int) time(&ss)%10 + 1;  
		printf("%s: got %d points\n", s, dice); 
    	points += dice;
		printf("%s: Total so far %d\n\n", s, points);  

		if(points >= 50)
		{
			printf("%s: game over I won\n", s); 
            kill(0, SIGTERM);
		}
		sleep(1);	// to slow down the execution  
		write(fd1, &turn, 1);  // child write to pipe 2, ie fd2
		// printf("TOTO Step 3\n"); //added

		close(fd1);
	}
}