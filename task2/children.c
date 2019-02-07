#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
  int child1=fork();

  int pid;

  if (child1 == 0)//child 1
    printf("I am child one, my pid is: %d\n",getpid());
  else 
  {
    pid = waitpid(child1, NULL, 0);
    if (child1 == pid) printf("child 1 has exited\n");
    return 0;
  }
  int child2=fork();
  if (child2 == 0)//child 2
      printf("I am child two, my pid is: %d\n",getpid());
  else
  { 
    pid = waitpid(child2, NULL, 0);
    if (child2 == pid) printf("child 2 has exited\n");
    return 0;
  }
  return 0;
}
