/*
============================================================================
Name : Program 18
Author : Hari Prasad C
Description : Write a program to find out total number of directories on the pwd.
              execute ls -l | grep ^d | wc ? Use only dup2.
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
        close (fd[0]);
        // STDOUT_FILENO will be closed since it was open previously
        dup2 ( fd[1], STDOUT_FILENO );

        execlp ("ls","ls","-l",NULL);
        close (fd[1]);
    } else {
        int fd1[2];

        if ( -1 == pipe (fd1)) {
            perror ("Pipe creation error");
            return -1;
        }
        
        close (fd[1]);
        int pid1 = fork();

        if ( pid1 ) {
            close (fd1[0]);

            dup2 ( fd[0], STDIN_FILENO);
            dup2 ( fd1[1], STDOUT_FILENO);

            execlp ("grep","grep","^d",NULL);

            close (fd[0]);
            close (fd1[0]);
        } else {
            close (fd[0]);
            close (fd1[1]);

            dup2 (fd1[0], STDIN_FILENO);

            execlp ("wc","wc",NULL);

            close (fd1[0]);            
        }
    }
    return 0;
}