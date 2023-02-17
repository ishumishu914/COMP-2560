#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
   //standard i/o
   char arr[] = "101   GM\tBuick\t2010\n102   Ford\tLincoln\t2005";
   FILE *fp = fopen("list_1.txt", "w"); // open file for writing

   for (int i = 0; arr[i] != NULL; i++)
   {
      fputc(arr[i], fp); // write to file with fputc
   }   

   return 0;
}