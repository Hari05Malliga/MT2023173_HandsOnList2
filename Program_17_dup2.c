/*
============================================================================
Name : Program 17
Author : Hari Prasad C
Description : Write a program to execute ls -l | wc, use dup2
Date: 3rd Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {
    int fd[2];

    if ( -1 == pipe(fd)) {
        perror ("Pipe create error");
        return -1;
    }

    int pid = fork();

    if (pid) {
        // STDOUT_FILENO will be closed since it was open previously
        dup2 ( fd[1], STDOUT_FILENO );
        close ( fd[0]);

        execlp ("ls","ls","-l",NULL);
        close (fd[1]);
    } else {
        // STDIN_FILENO will be closed since it was open previously
        dup2 ( fd[0], STDIN_FILENO );
        close ( fd[1] );

        execlp ("wc","wc",NULL);
        close ( fd[0] );
    }

    return 0;
}