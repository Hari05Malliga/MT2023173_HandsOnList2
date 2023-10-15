/*
============================================================================
Name : Program 29
Author : Hari Prasad C
Description : Write a program to remove the message queue.
Date: 6th Oct, 2023.
============================================================================
*/ 

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main () {
    key_t key;
    int msgid;
    struct msqid_ds msgQueInfo;

    // ftok to generate unique key
    key = ftok ("../", 86);

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

    if ( -1 == msgctl (msgid, IPC_RMID, &msgQueInfo)) {
        perror ("Unable to remove message queue");
        return -1;
    }
    
    return 0;
}

/*
output:
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ gcc Program_29.c -o Program_29
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x56062274 12         hari       644        0            0           

hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ./Program_29
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    

hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ 
*/