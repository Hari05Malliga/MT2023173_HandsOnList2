/*
============================================================================
Name : Program 31
Author : Hari Prasad C
Description : Write a program to create a semaphore and initialize value to the semaphore.
                a. create a binary semaphore
                b. create a counting semaphore
Date: 7th Oct, 2023.
============================================================================
*/ 

#include <sys/types.h> 
#include <sys/ipc.h>  
#include <sys/sem.h>  
#include <unistd.h>  
#include <stdio.h>  
#include <stdlib.h>

void main()
{
   key_t key;
   int id, status;

   union semun {
       int val; // Value of the semaphore
   } semSet;

   // Create a key for the semaphores.
   key = ftok ("../", 86);
   if (key == -1)
   {
       perror("Error while computing key!");
       exit(1);
   }

   // Create a semaphore set with 2 semaphores.
   id = semget(key, 2, IPC_CREAT | 0777);

   if(id == -1) {
       perror("Error while creating semaphore!");
       exit(1);
   }

   // Set the value of the binary semaphore to 1.
   semSet.val = 1; 
   status = semctl(id, 0, SETVAL, semSet);

   if(status == -1) {
       perror("Error while initalizing semaphore!");
       exit(0);
   }

   // Set the value of the counting semaphore to 5.
   semSet.val = 5;
   status = semctl(id, 1, SETVAL, semSet);

   if(status == -1) {
       perror("Error while initalizing semaphore!");
       exit(0);
   }

   exit(0);
}