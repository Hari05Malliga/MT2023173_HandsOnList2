/*
============================================================================
Name : Program 26
Author : Hari Prasad C
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 5th Oct, 2023.
============================================================================
*/      

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define MAX 100

struct msg_buffer {
    long msg_type;
    char msg_text[MAX];
} message;

int main () {
    key_t key;
    int msgid;

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

    printf ("Enter the message to be passed : ");
    memset ( message.msg_text, '\0', MAX);
    scanf ("%99[^\n]s", message.msg_text);

    message.msg_type = 5; // If not specified message is not getting pushed in message queue

    msgsnd (msgid, &message, sizeof(message), 0);
    return 0;
}

/*
output :
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    

hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ./Program_26 
Enter the message to be passed : This is first message.
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ./Program_26 
Enter the message to be passed : This is second message.
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x56062274 11         hari       666        224          2           
*/