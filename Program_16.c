/*
============================================================================
Name : Program 16
Author : Hari Prasad C
Description : Write a program to send and receive data from parent to child vice versa. Use two way communication.
Date: 3rd Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd1[2], fd2[2];

    if ( -1 == pipe(fd1) ) {
        perror ("Pipe creation error");
        return -1;
    }

    if ( -1 == pipe(fd2) ) {
        perror ("Pipe creation error");
        return -1;
    }

    int pid = fork();

    if ( pid ) {
        // fd1[1] is used for writing to child
        close (fd1[0]);
        char buf[100];

        printf ("[Parent sends] : ");
        scanf ("%99[^\n]s", buf);

        if ( -1 == write (fd1[1], &buf, sizeof(buf))) {
            perror ("Parent write error");
            return -1;
        }

        close (fd1[1]);

        // fd2[0] is used to read from child
        close (fd2[1]);
        memset (buf, '\0', sizeof(buf));

        if ( -1 == read (fd2[0], &buf, sizeof(buf))) {
            perror ("Parent read error");
            return -1;
        }

        printf ("[Parent receives] : %s\n", buf);
        close (fd2[0]);
    } else {
        // fd1[0] is used to read from parent
        close (fd1[1]);       
        char buf[100];

        if ( -1 == read (fd1[0], &buf, sizeof(buf))) {
            perror ("Child read error");
            return -1;
        }

        printf ("[Child receives] : %s\n", buf);
        close (fd1[0]);
        
        // fd2[1] is used for writing to parent
        close (fd2[0]);
        memset(buf, '\0', sizeof(buf));

        printf ("[Child sends] : ");
        scanf ("%99[^\n]s", buf);

        if ( -1 == write (fd2[1], &buf, sizeof(buf))) {
            perror ("Child write error");
            return -1;
        }

        close (fd2[1]);
    }

    return 0;
}