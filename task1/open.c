#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main (int argc, char *argv[])
{
  int fd;
  if(2 != argc)
  {
    printf("\n Usage:./open [file name] (Ex:./open simple.txt) \n");
    return 1;
   }

   errno = 0;
   fd = open(argv[1], O_RDWR|O_CREAT, S_IWRITE|S_IREAD);

   if (-1 == fd)
   {
     printf("\n open() failed with error [%s]\n", strerror(errno));
     return 1;
   }
   else
   {
     printf("\n open() Successful\n");
   }
   return 0;
}
