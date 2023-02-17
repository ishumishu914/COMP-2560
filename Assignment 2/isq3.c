#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
   char buf;
   int fd[argc-2]; //file descriptors for reading files (not including argv[0] & argv[-1]) 
   
   //open files
   for (int i = 0; i < argc-2; i++)
   {
      fd[i] = open(argv[i+1], O_RDONLY);
   }
   int fdw = open(argv[argc-1], O_WRONLY | O_APPEND);

   //file open error handling
   for (int i = 0; i < argc-2; i++)
   {
      if (fd[i] == -1)
      {
         printf("Error opening %s, exiting\n", argv[i]);
         exit(0);
      }        
   }

   //append to file
   for (int i = 0; i < sizeof(fd)/sizeof(int); i++)
   {
      while (read(fd[i], &buf, 1))
      {
         write(fdw, &buf, 1);
      }  
      write(fdw, "\n", 1);      
   }

   //print combined file content to terminal
   /*while (read(fdw, &buf, 1))
   {
      write(1, &buf, 1);
   }  
   write(1, "\n", 1);*/

   //close files
   for (int i = 0; i < argc-2; i++)
   {
      close(fd[i]);
   }
   close(fdw);  
   return 0;
}