/*
============================================================================
Name : Program 17
Author : Hari Prasad C
Description : Write a program to execute ls -l | wc, use fcntl
Date: 3rd Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd[2];
    if ( -1 == pipe (fd)) {
        perror ("Pipe creation error");
        return -1;
    }

    pid_t pid = fork();

    if (-1 == pid) {
        perror ("Child creation error");
        return -1;
    }

    if (pid) {
        // parent
        close (STDOUT_FILENO);
        fcntl (fd[1], F_DUPFD, STDOUT_FILENO);
        close (fd[0]);

        execlp ("/usr/bin/ls","ls","-l",NULL);
        close (fd[1]);
    } else {
        //child
        close (STDIN_FILENO);
        fcntl (fd[0], F_DUPFD, STDIN_FILENO);
        close (fd[1]);

        execlp ("/usr/bin/wc","wc",NULL);
        close (fd[0]);
    }
    return 0;
}