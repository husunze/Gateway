/*
 * rcvfromterm.c
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */

#include "rcvfromterm.h"

void rcvfromterm(key_t key)
{
    int qid, len;
    key_t mykey;
    char getmsg[BUF];
    struct mymsg pmsg;

    mykey = key;
    if ((qid = msgget(mykey, IPC_CREAT | 0666)) < 0)
    {
        perror("msgget error!");
        exit(1);
    }

    if ((len = msgrcv(qid, &pmsg, BUF, 0, 0)) > 0)
    {
        pmsg.msg_buf[len] = '\0';
        strcpy(getmsg, pmsg.msg_buf);
    }

}

