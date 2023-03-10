//******************************************************************
//getoccupier-- get occupier's name from residents file

#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

#define NAMELENGTH 41

char namebuf[NAMELENGTH]; // buffer to hold name
int infile = -1; //will hold file descriptor

char* getoccupier(int roomno)
{
	off_t offset;
	ssize_t nread;
	
	//open the file first time around
	if (infile == -1 && (infile = open("residents", O_RDONLY)) == -1)
	{
		return (NULL); // could not open the file
	}

	offset = (roomno - 1) * NAMELENGTH;

	//find room slot and read occupier's name
	if (lseek(infile, offset, SEEK_SET) == -1)
	{
		return (NULL);
	}

	if ((nread = read(infile, namebuf, NAMELENGTH)) <= 0)
	{
		return (NULL);
	}
	
	namebuf[nread - 1] = '\0';

	return (namebuf);
}


//**************************************************************************************************************************************************
//List All occupants's names
#define NROOMS 10

int main(int argc, char *argv[])
{
	int j;
	char* getoccupier(int), *p;

	for (int j = 1; j <= NROOMS; j++) 
	{
		if (p = getoccupier(j))
			printf("Room %2d, %s\n", j, p);
		else
			printf("Error on Room %d\n", j);
	}
}