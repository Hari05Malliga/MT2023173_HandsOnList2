/*
============================================================================
Name : Program 28
Author : Hari Prasad C
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
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

    if ( -1 == msgctl (msgid, IPC_STAT, &msgQueInfo)) {
        perror ("Unable to retrieve message queue information");
        return -1;
    }

    msgQueInfo.msg_perm.mode = 0644;
    if ( -1 == msgctl (msgid, IPC_SET, &msgQueInfo)) {
        perror ("Unable to change permission of message queue");
        return -1;
    }

    return 0;
}

/*
Output :
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ gcc Program_28.c -o Program_28
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x56062274 12         hari       666        0            0           

hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ./Program_28 
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x56062274 12         hari       644        0            0           

hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ 
*/