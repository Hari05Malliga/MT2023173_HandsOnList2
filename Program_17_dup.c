/*
============================================================================
Name : Program 17
Author : Hari Prasad C
Description : Write a program to execute ls -l | wc, use dup
Date: 3rd Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    if ( -1 == pipe (fd)) {
        perror ("Pipe creation error");
        return -1;
    }

    int pid = fork();

    if ( pid ) {
        close ( fd[0]);
        // closing STDOUT_FILENO and creating a new duplicate file descriptor with its value
        close (STDOUT_FILENO);
        dup (fd[1]);

        execlp ("ls", "ls", "-l", NULL);
        close (fd[1]);
    } else {
        close (fd[1]);
        // closing STDIN_FILENO and creating a new duplicate file descriptor with its value
        close (STDIN_FILENO);
        dup (fd[0]);

        execlp ("wc","wc", NULL);
        close (fd[0]);
    }
    return 0;
}