/*
============================================================================
Name : Program 25
Author : Hari Prasad C
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
                a. access permission
                b. uid, gid
                c. time of last message sent and received
                d. time of last change in the message queue
                d. size of the queue
                f. number of messages in the queue
                g. maximum number of bytes allowed
                h. pid of the msgsnd and msgrcv
Date: 5th Oct, 2023.
============================================================================
*/     

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

int main () {
    key_t key;
    int msgid;
    struct msqid_ds msgQueInfo;

    key = ftok ("../", 86);
    if ( -1 == key ) {
        perror ("Unable to generate key");
        return key;
    }

    msgid = msgget (key, IPC_CREAT | 0666);
    if ( -1 == msgid ) {
        perror ("Unable to create message queue");
        return msgid;
    }

    if ( -1 == msgctl (msgid, IPC_STAT, &msgQueInfo)) {
        perror ("Unable to retrieve message queue information");
        return -1;
    }

    printf("Access Permission: %od\n", msgQueInfo.msg_perm.mode);
    printf("UID: %d\n", msgQueInfo.msg_perm.uid);
    printf("GID: %d\n", msgQueInfo.msg_perm.gid);
    printf("Time of last sent message: %ld\n", msgQueInfo.msg_stime);
    printf("Time of last received message: %ld\n", msgQueInfo.msg_rtime);
    printf("Size of queue: %ld\n", msgQueInfo.__msg_cbytes);
    printf("Number of messages in the queue: %ld\n", msgQueInfo.msg_qnum);
    printf("Maximum number of bytes allowed in the queue: %ld\n", msgQueInfo.msg_qbytes);
    printf("PID of Process last sent message: %d\n", msgQueInfo.msg_lspid);
    printf("PID of Process last received message: %d\n", msgQueInfo.msg_lrpid);

    return 0;
}

/*
output:
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ gcc Program_26.c -o Program_26
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ gcc Program_27.c -o Program_27
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    

hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ gcc Program_25.c -o Program_25
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ./Program_26
Enter the message to be passed : This is first message.
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ./Program_27
Message received with 0 as flag : This is first message.
Message received with IPC_NOWAIT as flag : Message Queue Empty...
Message received with IPC_NOWAIT as flag : Message Queue Empty...
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ./Program_25
Access Permission: 666d
UID: 1000
GID: 1000
Time of last sent message: 1696430479
Time of last received message: 1696430489
Size of queue: 0
Number of messages in the queue: 0
Maximum number of bytes allowed in the queue: 16384
PID of Process last sent message: 16812
PID of Process last received message: 16816
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ 
*/