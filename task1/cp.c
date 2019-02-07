#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
  int rdfd,wrfd,fileread,fdsize;
  char buffer[100];

  if(3 != argc)
  {
    printf("\n Usage:./cp [file name (copy)] [file name (paste)] (Ex:./cp copy.txt paste.txt) \n");//add message
    return 1;
   }
   errno = 0;


   rdfd = open(argv[1], O_RDONLY);
   wrfd = open(argv[2], O_WRONLY|O_CREAT, S_IWRITE|S_IREAD);
   if (-1 == rdfd && -1 == wrfd)
   {
     printf("\nopen() failed with error [%s]\n", strerror(errno));
     return 1;
   }
   else
   {
     printf("\nopen() Successful\n");
     fdsize = lseek(rdfd,0L,SEEK_END);
     //printf("size of the file:%d\n", fdsize);// this code for check file's size
     lseek(rdfd,0L,SEEK_SET);

     while (fdsize > 0)
     {
      //read message from file
      fileread = read(rdfd,buffer,sizeof(buffer));
     
      //read message from file
      write(wrfd,buffer,fileread);
      fdsize=fdsize-100;
     }
     printf("copy() Successful\n");
   }
   close(rdfd);
   close(wrfd);
   return 0;
}
