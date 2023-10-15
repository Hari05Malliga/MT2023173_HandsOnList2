/*
============================================================================
Name : Program 21
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
#include <string.h>

int main () {

    if (access("myfifo",F_OK)) mkfifo ("myfifo", 0666);

    int fd = open ("myfifo", O_RDONLY);
    char buf[100];
    if ( -1 == read (fd, &buf, sizeof(buf))) {
        perror ("FIFO read error");
        return -1;
    }

    printf ("Message read from Named FIFO : %s\n", buf);

    if (access("myfifo1", F_OK)) mkfifo("myfifo1", 0666);

    int fd1 = open ("myfifo1", O_WRONLY);
    printf ("Message to be passed : ");

    memset (buf, '\0', sizeof(buf));
    scanf ("%99[^\n]s", buf);

    if ( -1 == write ( fd1, &buf, sizeof(buf))) {
        perror ("FIFO write error");
        return -1;
    }
    close (fd1);

    return 0;
}