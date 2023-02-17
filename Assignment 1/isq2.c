#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
   //system i/o
   int fd;
   char Array[] = "101   GM\tBuick\t2010\n102   Ford\tLincoln\t2005\n";
   fd = open("list1.txt", O_WRONLY | O_CREAT | O_TRUNC);
   write(fd, Array, sizeof (Array) -1);   // last char is a null pointer
   close(fd);

   return 0;
}