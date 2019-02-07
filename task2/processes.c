#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  int a=10, b=25, fq=0, fr=0;
  fq=fork(); //fork a child - call it Process Q
  if(fq==0)  //Child successfully forked
  {
    a=a+b;
    printf("I am child 1:\nThe value of a is %d, b is %d, and process_id is %d\n", a, b, getpid());
    fr=fork(); //fork another child - call it Process R
    if(fr!=0)  //second child NOT successfully forked 
    {
      b=b+20;
      printf("I am parent of child 2 (so child 1 = parent of child 2):\nThe value of a is %d, b is %d, and process_id is %d\n", a, b, getpid());
    }
    else
    {
      a=(a*b)+30;
      printf("I am child 2:\nThe value of a is %d, b is %d, and process_id is %d\n", a, b, getpid());
    }
   }
   else 
   {
     b=a+b-5;
     printf("I am parent:\nThe value of a is %d, b is %d, and process_id is %d\n", a, b, getpid());
   }
   return 0;
}
