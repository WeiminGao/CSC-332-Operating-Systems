#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include </usr/include/pthread.h>

#include "sem.h"


#define N 3
#define BUFSIZE 1  
#define PERMS 0666 //0666 - To grant read and write permissions 

int *buffer;
int nextp=0,nextc=0;
int mutex,full,empty;    /* semaphore variables
						  * mutex - binary semaphore -- critical section
 						  *	full, empty - counting semaphore */

void producer()
{
 int data;
 if(nextp == N)
 	nextp=0;
 printf("\nEnter the data(producer) :");
 scanf("%d",(buffer+nextp));
 nextp++;
 }

void *consumer(void *vargp)
{
 int g;
 if(nextc == N)
 	nextc=0;
 g=*(buffer+nextc++);
 printf("\nconsumer consumes the data:%d\n",g);
 pthread_exit(0);
}

int main()
{
 int i;
 pid_t pid;
 pthread_t tid;
 pthread_attr_t attr;
 
//forking a child 
 if((pid=fork()) < 0)
 {
  printf("\n Error in process creation");
  exit(1);
 }
//Producer process (Parent)
 if(pid > 0)
 {
	for(i=0;i<N;i++)
	{
	  //P(empty); 
	  //P(mutex); // Entering critical section
	  producer();
	  //V(mutex); // Exit from critical section
	  //V(full); 
	}
        wait(NULL);
 }

//consumer process (Child)
 if(pid == 0)
 {
	 for(i=0;i<N;i++)
	 {
	  //P(full);
	  //P(mutex); // Entering critical section
          pthread_attr_init(&attr);
	  pthread_create(&tid, NULL, consumer, NULL);
          pthread_join(tid, NULL);
	  //V(mutex);
	  //V(empty); // Exit from critical section
	 }
  }
}
