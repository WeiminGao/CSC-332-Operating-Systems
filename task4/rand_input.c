#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main ()
{
  int students=10, grades=10;
  FILE *inpf;
  inpf = fopen("input_file.txt", "w");
  srand(time(NULL));
  for (int i=0; i<students; i++)
  {  for (int j=0; j<grades; j++)   
        fprintf(inpf,"%*d ",3, rand()%100);
     fprintf(inpf,"\n");
  }
  fclose(inpf);
}
