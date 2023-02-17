#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
   char c;
   //FILE *fp[argc-2]; 
   FILE** fp = malloc(sizeof(FILE)*(argc-2));  //file descriptors for reading files (not including argv[0] & argv[-1]) 

   //open files
   for (int i = 0; i < argc-2; i++)
   {
      fp[i] = fopen(argv[i+1], "r");
   }
   FILE *fpw = fopen(argv[argc-1], "a");

   //file open error handling
   for (int i = 0; i < argc-2; i++)
   {
      if (fp[i] == NULL)
      {
         printf("Error opening %s, exiting\n", argv[i]);
         exit(0);
      }        
   }

   //append to file
   for (int i = 0; i < sizeof(fp)/sizeof(int); i++)
   {
      c = fgetc(fp[i]);
      while (c != EOF)
      {
         fputc(c, fpw);
         c = fgetc(fp[i]);
      }
      fputc('\n', fpw);
   }
   
   //close file pointers
   for (int i = 0; i < argc-2; i++)
   {
      //fclose(fp[i]);
      free(fp[i]);
   }
   fclose(fpw);
      
   return 0;
}