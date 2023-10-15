/*
============================================================================
Name : Program 20 
Author : Hari Prasad C
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 4th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main () {
    if (access("myfifo", F_OK)) mkfifo("myfifo", 0666);

    int fd = open ("myfifo", O_WRONLY);
    printf ("Message to be passed : ");

    char buf[100];
    scanf ("%99[^\n]s", buf);

    if ( -1 == write ( fd, &buf, sizeof(buf))) {
        perror ("FIFO write error");
        return -1;
    }
    close (fd);
    return -1;
}