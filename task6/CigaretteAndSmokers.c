#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "sem.h"

 
#define PERMS 0666 //0666 - To grant read and write permissions 

int lock, agent;
int smoker_paper, smoker_tobacco, smoker_match; 
int randNum;
const char *ingredients[3]  = {"tobacco", "paper", "match"};
						  

void Agent()
{
 randNum = rand() % 3;
 if(randNum == 0)
	{
	  printf("Put tobacco and paper on the table\n");
	  sleep(1);
	  V(smoker_match); // Wake up the smoker with match
	}
 else if(randNum == 1)
	{
	  printf("Put tobacco and match on the table\n");
	  sleep(1);
	  V(smoker_paper); // Wake up the smoker with paper
	}
 else if(randNum == 2)
	{
	  printf("Put match and paper on the table\n");
	  sleep(1);
	  V(smoker_tobacco); // Wake up the smoker with tobacco
	}
 }


void Smokers(int number){
	P(lock);
	printf("Smoker#%d with %s picks up %s and %s\n", number, ingredients[number-1], ingredients[(number)%3], ingredients[(number+1)%3]);
	//One Smoker pick up other two ingredients in table.
 	sleep(1);
     	V(agent);
     	V(lock);
     	printf("Smoker#%d smokes!\n", number); //Smoker smokes.
}


int main()
{
 int shmid,i;
 int pid, status;
 int N=20;       // Number of times the agent will put ingredients on table


 // semaphore creation
 if((lock=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
    {
	printf("\n can't create mutex semaphore");
  	exit(1);
    }

 if((agent=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
    {
	printf("\n can't create mutex semaphore");
  	exit(1);
    }

 if((smoker_paper=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
    {
	printf("\n can't create mutex semaphore");
  	exit(1);
    }

 if((smoker_tobacco=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
    {
	printf("\n can't create mutex semaphore");
  	exit(1); 
    }

 if((smoker_match=semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
    {
	printf("\n can't create mutex semaphore");
  	exit(1);
    }

 // initialze the semaphore 	
sem_create(lock,1);
sem_create(agent,0);
sem_create(smoker_paper,0);
sem_create(smoker_tobacco,0);
sem_create(smoker_match,0);


//forking a child 
 if((pid=fork()) < 0)
 {
  printf("\n Error in process creation");
  exit(1);
 }

//Smokers process
 if(pid > 0)
 {
	for(i=0;i<N;i++)
	{
	  // Smoker#1 Process
	  if ((pid = fork()) == -1) // Check for a fork error
	  {
	    perror("Fork failed!");
	    exit(1);
	  }
	  if (pid == 0)
	  {
	    while(1)
	    {
	     	P(smoker_tobacco); // Sleep right away
	     	Smokers(1); //Smoker#1 has tobacco
	    }
	   }
	   else
	   {
	     //Smoker#2 Process
	     if ((pid = fork()) == -1) // Check for a fork error
	     {
	      	perror("Fork failed!");
	      	exit(1);
	     }
	     if (pid == 0)
	     {
	      while(1)
	      {
		P(smoker_paper); // Sleep right away
	     	Smokers(2);//Smoker#2 has paper 
	      }
            }
	    else
	    { 
	      //Smoker#3 Process
	      if ((pid = fork()) == -1) // Check for a fork error
	      {
	      	perror("Fork failed!");
		exit(1);
	      }
	      if (pid == 0)
	      {
	       while(1)
	       {
		  P(smoker_match); // Sleep right away
		  Smokers(3);//Smoker#3 has match
	       }
              }
	      else
	      {
		pid = wait(&status);
	        printf("Process with pid = %d exited with the status %d. \n", pid, status);
	      }
	     }
	   }
         }
 }

//Agent process
if(pid == 0)
	{
	 for(i=0;i<N;i++)
	 {
	   P(lock);
	   Agent();
	   V(lock);
	   P(agent); // Agent sleeps
	 }
        }
	exit(0); 
}
