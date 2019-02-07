#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *arv[])
{ 
  int child=fork();
  //char *const parmList[] = {"/bin/ls","-la","/usr/bin", NULL};
  arv[0] = "/bin/ls";
  arv[1] = "-la";
  arv[2] = "/usr/bin";
  arv[3] = NULL;
  if (child == -1)
    perror("fork error");
  else if (child == 0)
  {
    printf("The child processes successfully: %d\n", getpid());
    execvp("ls",arv);
    printf ("EXECV Failed\n");
  }
  else {
    waitpid(child, NULL, 0);
  }
}

