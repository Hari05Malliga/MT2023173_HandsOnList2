/*
============================================================================
Name : Program 14
Author : Hari Prasad C
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
Date: 3rd Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>

int fd[2];

// read from pipe and display in monitor

void read_func () {
    char buf[100];
    // printf ("Message read from pipe : ");

    if ( -1 == read (fd[0], &buf, sizeof(buf)) ) {
        perror ("Pipe read error");
        exit(0);
    }

    printf ("Message read from pipe : ");
    printf ("%s \n", buf);
    close(fd[0]);
}

// write into pipe 

void write_func () {
    char buf[100];
    printf ("Message to be passed : ");
    scanf ("%99[^\n]s", buf);

    if ( -1 == write (fd[1], &buf, sizeof(buf)) ) {
        perror ("Pipe write error");
        exit(0);
    }
    close(fd[1]);
}

int main() {

    // Pipe Creation

    if ( -1 == pipe(fd) ) {
        perror ("Pipe creation error");
        return -1;
    }

    pthread_t read, write;
    pthread_create ( &read, NULL, (void *) read_func, NULL);
    pthread_create ( &write, NULL, (void *) write_func , NULL);

    pthread_join( read, NULL);
    pthread_join ( write, NULL);
    return 0;
}