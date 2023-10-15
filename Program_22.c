/*
============================================================================
Name : Program 23
Author : Hari Prasad C
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
              system call with FIFO.
Date: 5th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>

int main () {
    if (access("myfifo", F_OK)) mkfifo("myfifo", 0666);

    int fd = open ("myfifo", O_WRONLY);
    printf ("Message to be passed : ");
    fflush(stdout);

    fd_set read_fd;
    FD_ZERO (&read_fd);

    FD_SET ( STDIN_FILENO, &read_fd);

    struct timeval target_time;

    target_time.tv_sec = 10;
    target_time.tv_usec = 0;

    int val = select ( STDIN_FILENO+1 , &read_fd, NULL, NULL, &target_time);
    if ( !val ) printf ("\nWaiting time expired...\n");
    else {
        char buf[100];
        scanf ("%99[^\n]s", buf);

        if ( -1 == write ( fd, &buf, sizeof(buf))) {
            perror ("FIFO write error");
            return -1;
        }
    }

    close (fd);
    return -1;
}