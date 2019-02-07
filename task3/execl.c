#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *arv[])
{ 
  int child=fork();
  if (child == -1)
    perror("fork error");
  else if (child == 0)
  {
    printf("The child processes successfully: %d\n", getpid());
    execl("/bin/date","date",NULL);
    printf ("EXECV Failed\n");
  }
  else {
    waitpid(child, NULL, 0);
  }
}

