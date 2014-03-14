/*
 * sendtodb.c
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */

#include "sendtodb.h"

void sendtodb(char *s, key_t key)
{
    int qid, len;
    key_t mykey;
    struct mymsg pmsg;
    mykey = key;

    strcpy(pmsg.msg_buf, s);

    len = sizeof(pmsg.msg_buf);

    if ((qid = msgget(mykey, IPC_CREAT | 0666)) < 0)
    {
        perror("msgget error!");
        exit(1);
    }

    if ((msgsnd(qid, &pmsg, len, 0)) < 0)
    {
        perror("msgsnd error!");
        exit(1);
    }
}

