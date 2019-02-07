#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main (int argc, char *argv[])
{
   int fd1, fd2;
   
   argv[1] = "destination1.txt";
   argv[2] = "destination2.txt";
   fd1 = open(argv[1], O_RDWR|O_CREAT, S_IWRITE|S_IREAD);
   fd2 = open(argv[2], O_RDWR|O_CREAT, S_IWRITE|S_IREAD);

   if (-1 == fd1 || -1 == fd2)
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
