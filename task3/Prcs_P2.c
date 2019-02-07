#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
   int rdfd,wrfd1, wrfd2,fileread1,fileread2,fdsize;
   char buffer1[100];
   char buffer2[50];
   
   argv[1] = "source.txt";
   argv[2] = "destination1.txt";
   argv[3] = "destination2.txt";
   errno = 0;
   rdfd = open(argv[1], O_RDONLY);
   wrfd1 = open(argv[2], O_WRONLY);
   wrfd2 = open(argv[3], O_WRONLY);
   if (-1 == rdfd || -1 == wrfd1 || -1 == wrfd2)
   {
     printf("\nopen() failed with error [%s]\n", strerror(errno));
     return 1;
   }
   else
   {
     printf("\nopen() Successful\n");
     fdsize = lseek(rdfd,0L,SEEK_END);
     lseek(rdfd,0L,SEEK_SET);

     while (fdsize > 0)
     {
      //read 100 characters from source file
      fileread1 = read(rdfd,buffer1,sizeof(buffer1));
      for (int i=0; i<100; i++)
        if (buffer1[i] == '1') buffer1[i] = 'A';
      //write 100 characters to file 1
      write(wrfd1,buffer1,fileread1);
      fdsize=fdsize-100;
     
      if (fdsize > 0)
      {
        //read 50 characters from source file
        fileread2 = read(rdfd,buffer2,sizeof(buffer2));
        for (int i=0; i<50; i++)
           if (buffer2[i] == '2') buffer2[i] = 'B';
        //write 50 characters to file 2
        write(wrfd2,buffer2,fileread2);
        fdsize=fdsize-50;
      }
     }
     printf("Copy and encrypt Successful\n");
   }
   close(rdfd);
   close(wrfd1);
   close(wrfd2);
   return 0;
}
