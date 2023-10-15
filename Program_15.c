/*
============================================================================
Name : Program 15
Author : Hari Prasad C
Description : Write a simple program to send some data from parent to the child process.
Date: 3rd Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    if (-1 == pipe(fd)) {
        perror ("Pipe error creation");
        return -1;
    }

    int pid = fork();
    if ( pid ) {
        close(fd[0]);
        char buf[100];

        printf ("Message to be passed to child : ");
        scanf ("%99[^\n]s", buf);

        if ( -1 == write (fd[1], &buf, sizeof(buf)) ) {
            perror ("Pipe Write error");
            return -1;
        }

        close (fd[1]);
        wait(0);
    } else {
        close (fd[1]);
        char buf[100];
        
        if (-1 == read (fd[0], &buf, sizeof(buf)) ) {
            perror ("Pipe read error");
            return -1;
        }

        printf ("Message read from parent : ");
        printf ("%s \n", buf);

        close(fd[0]);
    }

    return 0;
}