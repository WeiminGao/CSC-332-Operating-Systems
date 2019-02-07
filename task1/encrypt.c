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
  char addbuff[]="XYZ";

  if(3 != argc)
  {
    printf("\n Usage:./cp [file name (source)] [file name (encrypt)] (Ex:./cp source.txt encrypt.txt) \n");//add message
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
      for (int i=0; i<100; i++)
        if (buffer[i] == '1') buffer[i] = 'A';

      //read message from file
      write(wrfd,buffer,fileread);
      write(wrfd,addbuff, 3);
      fdsize=fdsize-100;
     }
     printf("Copy and encrypt Successful\n");
   }
   close(rdfd);
   close(wrfd);
   return 0;
}
