#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
   FILE *fp1 = fopen(argv[1], "r+");
   FILE *fp2 = fopen(argv[2], "w");
   char buf[400];
   int ch, count;

   if(argc == 1)  
      fp1 = stdin;
   else if (argc < 3)
      printf("Wrong number of inputs!");
   
   else
   {
      if(fp1 == NULL)
      {
         printf("Error opening %s, exiting\n", argv[1]);  	 		
         exit(0);
      }
   }

   fseek(fp1, 0, SEEK_END);
   fprintf(fp1, " ");
   
   while (ftell(fp1) > 1)
   {
      fseek(fp1, -2, SEEK_CUR);
      if (ftell(fp1) < 2)
         break;

      ch = fgetc(fp1);
      count = 0;
      while (ch != '\n')
      {
         buf[count++] = ch;
         if (ftell(fp1) < 2)
            break;

         fseek(fp1, -2, SEEK_CUR);
         ch = fgetc(fp1);
      }
      
      for (int i = (count-1); i >= 0; i--)
      { 
         fprintf(fp2, "%c", buf[i]);
      }  
      fprintf(fp2, "\n");
   }
   
   fclose(fp1);
   fclose(fp2);
   exit(0);
   return 0;
}