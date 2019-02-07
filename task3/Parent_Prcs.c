#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
  int child1=fork();

  int pid;

  if (child1 == 0)//child 1
  {
    printf("I am child one, my pid is: %d\n",getpid());
    execv ("/home/cslab/csstudent/gaow3242/Documents/task3/Prcs_P1", &argv[0]);
  }
  else 
  {
    waitpid(child1, NULL, 0);
  }
  int child2=fork();
  if (child2 == 0)//child 2
  {
      printf("\nI am child two, my pid is: %d\n",getpid());
      execv ("/home/cslab/csstudent/gaow3242/Documents/task3/Prcs_P2", &argv[0]);
  }
  else
  { 
     waitpid(child2, NULL, 0);
  }
  return 0;
}
