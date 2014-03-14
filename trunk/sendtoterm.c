/*
 * sendtoterm.c
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */

#include "sendtoterm.h"

void sendtoterm(char *ip, int id, key_t key)
{
    int qid, len;
    int size;
    key_t mykey;
    struct mymsg pmsg;
    int i, j;
    char idtemp[MAX];
    mykey = key;
    size = strlen(ip);
    memset(pmsg.msg_buf, 0, 512);
    pmsg.msg_types = 1;

    for (i = 0; i < size; i++)
        pmsg.msg_buf[i] = ip[i];/*第一个字段为要发送机器的ip*/
    for (j = 19; j >= size; j--)
        pmsg.msg_buf[j] = '#';

    sprintf(idtemp, "%d", id);
    size = strlen(idtemp);
    for (i = 0; i < size; i++)
        pmsg.msg_buf[i + 20] = idtemp[i];
    for (j = 19; j >= size; j--)
        pmsg.msg_buf[j + 20] = '#';

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
    printf("send into queue 'z'\n");
}

