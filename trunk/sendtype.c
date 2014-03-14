/*
 * sendtype.c
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */

#include "sendtype.h"

void sendtype1(char *ip, struct TypeMsg1 s1, key_t key)
{
    int i, j;
    int qid, len;
    int size;
    char temp[MAX];
    key_t mykey;
    struct mymsg pmsg;
    mykey = key;
    memset(pmsg.msg_buf, 0, 512);
    pmsg.msg_types = 1;
    sprintf(temp, "%s", ip);
    size = strlen(temp);
    for (i = 0; i < size; i++)
        pmsg.msg_buf[i] = temp[i];
    for (j = 19; j >= size; j--)
        pmsg.msg_buf[j] = '#';/*不足二十个用#号填充*/

    sprintf(temp, "%d", s1.sourceID);
    size = strlen(temp);
    for (i = 0; i < size; i++)
        pmsg.msg_buf[i + 20] = temp[i];
    for (j = 19; j >= size; j--)
        pmsg.msg_buf[j + 20] = '#';/*不足二十个用#号填充*/

    sprintf(temp, "%d", s1.destinationID);
    size = strlen(temp);
    for (i = 0; i < size; i++)
        pmsg.msg_buf[i + 40] = temp[i];
    for (j = 19; j >= size; j--)
        pmsg.msg_buf[j + 40] = '#';/*不足二十个用#号填充*/

    for (i = 0; i < 20; i++)
        pmsg.msg_buf[i + 60] = '#'; /*这是一对一的type表，第二个目的为空，用#填充*/

    sprintf(temp, "type%d", s1.type);
    size = strlen(temp);
    for (i = 0; i < size; i++)
        pmsg.msg_buf[i + 80] = temp[i];
    for (j = 19; j >= size; j--)
        pmsg.msg_buf[j + 80] = '#';/*不足二十个用#号填充*/

    len = sizeof(pmsg.msg_buf);

    if ((qid = msgget(mykey, IPC_CREAT | 0666)) < 0)
    {
        perror("msgget error!");
        exit(1);
    }
    in("send type1\n");
    if ((msgsnd(qid, &pmsg, len, 0)) < 0)
    {
        perror("msgsnd error!");
        exit(1);
    }
}

void sendtype2(char *ip, struct TypeMsg2 s2, key_t key)
{
    int i, j;
    int qid, len;
    int size;
    char temp[MAX];
    key_t mykey;
    struct mymsg pmsg;
    mykey = key;
    memset(pmsg.msg_buf, 0, 512);
    pmsg.msg_types = 1;
    strcpy(temp, ip);
    size = strlen(temp);
    for (i = 0; i < size; i++)
        pmsg.msg_buf[i] = temp[i];
    for (j = 19; j >= size; j--)
        pmsg.msg_buf[j] = '#';/*不足二十个用#号填充*/

    sprintf(temp, "%d", s2.sourceID);
    size = strlen(temp);
    for (i = 0; i < size; i++)
        pmsg.msg_buf[i + 20] = temp[i];
    for (j = 19; j >= size; j--)
        pmsg.msg_buf[j + 20] = '#';/*不足二十个用#号填充*/

    sprintf(temp, "%d", s2.destinationID1);
    size = strlen(temp);
    for (i = 0; i < size; i++)
        pmsg.msg_buf[i + 40] = temp[i];
    for (j = 19; j >= size; j--)
        pmsg.msg_buf[j + 40] = '#';/*不足二十个用#号填充*/

    sprintf(temp, "%d", s2.destinationID2);
    size = strlen(temp);
    for (i = 0; i < size; i++)
        pmsg.msg_buf[i + 60] = temp[i];
    for (j = 19; j >= size; j--)
        pmsg.msg_buf[j + 60] = '#';/*不足二十个用#号填充*/

    sprintf(temp, "type%d", s2.type);
    size = strlen(temp);
    for (i = 0; i < size; i++)
        pmsg.msg_buf[i + 80] = temp[i];
    for (j = 19; j >= size; j--)
        pmsg.msg_buf[j + 80] = '#';/*不足二十个用#号填充*/

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

