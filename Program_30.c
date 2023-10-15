/*
============================================================================
Name : Program 30
Author : Hari Prasad C
Description : Write a program to create a shared memory.
                a. write some data to the shared memory
                b. attach with O_RDONLY and check whether you are able to overwrite.
                c. detach the shared memory
                d. remove the shared memory
Date: 6th Oct, 2023.
============================================================================
*/ 

#include <sys/types.h> 
#include <sys/ipc.h>  
#include <sys/shm.h>   
#include <unistd.h>   
#include <stdio.h>   
#include <stdlib.h>

void main()
{
    key_t key;         
    int id;    
    ssize_t size = 50; 
    char *smp, *rdSmp;

    key = ftok ("../", 86);

    if (-1 == key)
    {
        perror("Error while computing key!");
        exit(0);
    }

    id = shmget(key, size, IPC_CREAT | 0700); // Create the shared memory if it doesn't exist; if it exists use the existing one

    if (-1 == id)
    {
        perror("Error while getting Shared Memory!");
        exit(0);
    }

    // a. write some data to the shared memory

    smp = shmat(id, NULL, SHM_W | SHM_R);

    if (-1 == *smp)
    {
        perror("Error while attaching address space!");
        exit(0);
    }

    printf("Press enter to write to the shared memory!\n");
    getchar();

    sprintf(smp, "Hello, How are you?\n");

    printf("Press enter to read from the shared memory!\n");
    getchar();

    printf("Data from shared memory: %s\n", smp); // Reading from the shared memory

    // b. attach with O_RDONLY and check whether you are able to overwrite.

    rdSmp = shmat(id, NULL, SHM_RDONLY);
    if (*rdSmp == -1)
    {
        perror("Error while attaching address space!");
        exit(0);
    }
    
    // printf("Press enter to write to the shared memory!\n");
    // getchar();

    // The below line will cause a segmentation fault (uncomment to get the required output)
    // sprintf(rdSmp, "Causes Segmentation Fault (core dumped)");

    printf("Press enter to read from the shared memory!\n");
    getchar();

    printf("Data from shared memory: %s\n", rdSmp); // Reading from the shared memory

    // c. detach the shared memory

    printf("Press enter to detaching pointer to shared memory!\n");
    getchar();

    shmdt(smp);      
    shmdt(rdSmp);    

    // d. remove the shared memory

    printf("Press enter to delete the shared memory!\n");
    getchar();

    shmctl(id, IPC_RMID, NULL);
}