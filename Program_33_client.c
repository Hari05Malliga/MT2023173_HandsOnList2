/*
============================================================================
Name : Program 33
Author : Hari Prasad C
Description : Write a program to communicate between two machines using socket.
Date: 9th Oct, 2023.
============================================================================
*/ 

// Client Side Program

#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>      
#include <unistd.h> 
#include <string.h>

int main () {
    int fd;

    struct sockaddr_in address;
    char buff[100];

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( -1 == fd ) {
        perror ("Unable to create socket");
        return -1;
    }

    printf ("Client Side Socket Created...\n");

    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    if ( -1 == connect (fd, (struct sockaddr *) &address, sizeof(address))) {
        perror ("Error while trying to connect to server");
        return -1;
    }

    printf ("Client to server connection is succefully established.\n");

    size_t read_size = read(fd, buff, sizeof(buff));
    if ( -1 == read_size ) {
        perror ("Error while reading from network via socket");
        return -1;
    }

    printf("Server : %s\n", buff);

    size_t write_size = write(fd, "I am client.", 12 );
    if (-1 == write_size) {
        perror ("Error while writing to network via socket");
        return -1;
    }

    printf ("Data sent successfully.\n");

    close (fd);
    return 0;
}