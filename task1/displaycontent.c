#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
  int fd;
  char buffer[100];
  char inform[100];

  if(2 != argc)
  {
    printf("\n Usage:./displaycontent [file name] (Ex:./displaycontent simple.txt) \n");
    return 1;
   }
   errno = 0;
   fd = open(argv[1], O_RDWR);

   if (-1 == fd)
   {
     printf("\nopen() failed with error [%s]\n", strerror(errno));
     return 1;
   }
   else
   {
     printf("\nopen() Successful\n");
     
     //read message from file
     read(fd,buffer,sizeof(buffer));
     printf("\nOutput->%s\n", buffer);

     //write message to file
     printf("Enter the message:\n");
     scanf("%[^\n]%*c",inform);
     write(fd,inform,strlen(inform));
   }

   //close file
   close(fd);
   return 0;
}
