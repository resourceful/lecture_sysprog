#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define MSGSZ     128

/* the message structure. */
typedef struct mymesg {
         long    mtype;
         char    mtext[MSGSZ];
         } message_buf;

int main()
{
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    message_buf sbuf;
    size_t buf_length;

    if((key = ftok("Makefile", 'R')) == -1){
        perror("ftok");
        exit(1);
    }

    fprintf(stderr, "\nmsgget: Calling msgget(%#x, %#o)\n", key, msgflg);

    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        exit(1);
    }
    fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);

    /*  We'll send message type 1 */
    sbuf.mtype = 1;
    printf("Enter a message to add to the message queue: ");
    scanf("%[^\n]", sbuf.mtext);
    getchar();

    buf_length = strlen(sbuf.mtext) + 1 ;

    /* Send a message.*/
    if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
       printf ("%d, %ld, %s, %ld\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
        perror("msgsnd");
        exit(1);
    } else 
      printf("Message: \"%s\" Sent\n", sbuf.mtext);

    exit(0);
}
