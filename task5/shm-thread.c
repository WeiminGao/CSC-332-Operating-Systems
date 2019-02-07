#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include </usr/include/pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* the size (in bytes) of shared memory object */
const int SIZE = 4096;
/* name of the shared memory object */
const char* name = "OS";
/* strings written to shared memory */
const char *message0= "Studying ";
const char *message1= "Operating Systems ";
const char *message2= "Is Fun!";
/* shared memory file descriptor */
int shm_fd;
/* pointer to shared memory obect */
void* ptr;

struct arg_struct{
   int intarg;
};

void *producer (void *vargp){
    struct arg_struct *arg = vargp;
    printf("\nI am producer %d.\n", arg->intarg);
    /* configure the size of the shared memory object */
    ftruncate(shm_fd, SIZE);
 
    /* memory map the shared memory object */
    ptr = mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
 
    /* write to the shared memory object */
    sprintf(ptr,"%s",message0);
    ptr += strlen(message0); 
    sprintf(ptr,"%s",message1);
    ptr += strlen(message1);
    sprintf(ptr,"%s",message2);
    ptr += strlen(message2);
}

void *consumer (void *vargp){
    struct arg_struct *arg = vargp;
    printf("\nI am consumer %d.\n", arg->intarg);
    /* memory map the shared memory object */
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    /* read from the shared memory object */
    printf("%s\n", (char*)ptr);
}
 
int main()
{
    pthread_t tid;
    struct arg_struct arg;
    /* create the shared memory object */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
 
    /* configure the size of the shared memory object */
    ftruncate(shm_fd, SIZE);

    for(int i=0;i<3;i++){
       arg.intarg=i;
       pthread_create(&tid, NULL, producer, &arg);
       pthread_join(tid, NULL); 

       pthread_create(&tid, NULL, consumer, &arg);
       pthread_join(tid, NULL);
    }
 
    /* remove the shared memory object */
    shm_unlink(name);
    return 0;
}
