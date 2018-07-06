#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define MSGSZ     128

/* Declare the message structure */

typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;


int main()
{
    int msqid;
    key_t key;
    message_buf  rbuf;

    if((key = ftok("Makefile", 'R')) == -1){
        perror("ftok");
        exit(1);
    }

    if ((msqid = msgget(key, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    /* Receive an answer of message type 1. */
    if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    /* Print the answer. */
    printf("%s\n", rbuf.mtext);
    exit(0);
}
