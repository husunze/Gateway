/*
 * getconn.c
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */

#include "getconn.h"
int getconn(key_t key, char* ipMsg, char* status)
{
    struct mymsg lmsg;
    int qid, len;
    key_t mykey;
    mykey = key;
    int i;
    if ((qid = msgget(mykey, IPC_CREAT | 0666)) < 0)
    {
        perror("msg read error");
        exit(1);
    }
    printf("qid of auot_reg:%d \n", qid);
    if ((len = msgrcv(qid, &lmsg, BUF, 0, 0)) > 0)
    {
        lmsg.msg_buf[len] = '\0';
        printf("Get a message:\n");
        printf("read message:%s=======from the Q:%d\n", lmsg.msg_buf, qid);
        printf("====================================================\n");
        for (i = 0; i < 20; i++)
        {
            if (lmsg.msg_buf[i] != '#')
                ipMsg[i] = lmsg.msg_buf[i];
            else
                break;
        }
        ipMsg[i] = '\0';
        for (i = 0; i < 10; i++)
        {
            if (lmsg.msg_buf[i + 20] != '#')
                status[i] = lmsg.msg_buf[i + 20];
            else
                break;
        }
        status[i] = '\0';
        return len;
    }
}

