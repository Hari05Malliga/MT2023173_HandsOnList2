/*
============================================================================
Name : Program 24
Author : Hari Prasad C
Description : Write a program to create a message queue and print the key and message queue id.
Date: 5th Oct, 2023.
============================================================================
*/      

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main () {
    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok (".", 23);

    if ( -1 == key) {
        perror ("Unable to generate key");
        return key;
    }

    // msgget creates a message queue and returns identifier
    msgid = msgget (key, 0666 | IPC_CREAT);

    if ( -1 == msgid ) {
        perror ("Unable to create message queue");
        return msgid;
    }

    printf ("Key : %d \nMessage Queue id : %d\n", key, msgid);
    return 0;
}

/*
output:
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ gcc Program_24.c -o Program_24
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ./Program_24 
Key : 386276798 
Message Queue id : 13
*/