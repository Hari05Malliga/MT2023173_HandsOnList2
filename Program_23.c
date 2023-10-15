/*
============================================================================
Name : Program 22
Author : Hari Prasad C
Description : Write a program to print the maximum number of files can be opened within a process and
              size of a pipe (circular buffer).
Date: 5th Oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main () {
    long PIPE_BUF, OPEN_MAX;

    PIPE_BUF = pathconf (".", _PC_PIPE_BUF);
    OPEN_MAX = sysconf (_SC_OPEN_MAX);

    printf ("pipe_buf = %ld\nOpen_max = %ld\n", PIPE_BUF, OPEN_MAX);
    return 0;   
}   