/*
============================================================================
Name : Program 27
Author : Hari Prasad C
Description : Write a program to receive messages from the message queue.
                a. with 0 as a flag
                b. with IPC_NOWAIT as a flag
Date: 6th Oct, 2023.
============================================================================
*/      

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>
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

    msgrcv (msgid, &message, sizeof(message), 5, 0);
    printf ("Message received with 0 as flag : %s\n", message.msg_text);
    memset (message.msg_text, '\0', MAX);

    msgrcv (msgid, &message, sizeof(message), 5, IPC_NOWAIT);
    printf ("Message received with IPC_NOWAIT as flag : ");
    if ( errno != ENOMSG )  printf ("%s\n", message.msg_text);
    else    printf ("Message Queue Empty...\n");

    msgrcv (msgid, &message, sizeof(message), 9, IPC_NOWAIT);
    printf ("Message received with IPC_NOWAIT as flag : ");
    if ( errno != ENOMSG )  printf ("%s\n", message.msg_text);
    else    printf ("Message Queue Empty...\n");

    return 0;
}

/*
output :
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ./Program_26
Enter the message to be passed : This is first message.
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ./Program_26
Enter the message to be passed : This is second message.
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x56062274 12         hari       666        224          2           

hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$ ./Program_27
Message received with 0 as flag : This is first message.
Message received with IPC_NOWAIT as flag : This is second message.
Message received with IPC_NOWAIT as flag : Message Queue Empty...
hari@hari-Sword-15-A12VF:~/Desktop/Software_System/Assignment2$
*/