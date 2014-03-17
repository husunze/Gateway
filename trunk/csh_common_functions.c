/*
 * csh_common_functions.c
 *
 *  Created on: 2013年8月13日
 *      Author: oracle
 */

#include "csh_common_functions.h"

/**发送消息到指定的队列
*key为消息队列的关键字
*isContainType为常量，只能为0或1，0表示发送消息队列中不包括消息类型
*/
int csh_sendMessageToQueue(key_t key,int isContainType,struct mymsg * msg)
{
    /*        printf("send one message\n");*/
    int qid;
    int result;
    int length;/*发送消息的长度*/
    if((qid=msgget(key,0666|IPC_CREAT))<0)
    {
        perror("msgget");
        exit(1);
    }
    /*根据isContainType的值来判断发送消息的长度*/
    if(isContainType==1) /*说明发送的消息要包括消息类型*/
    {
        length=sizeof( *msg);
    }
    else if(isContainType==0)
    {
        length=512;
    }
    else
    {
        printf("can shu lei xing errors");
        exit(1);
    }
    if((result=msgsnd(qid,msg,length,0))<0)
    {
        perror("msgsn");
        exit(1);
    }
    /*	printf("\nend of send msg\n");*/
    return result;
}

void  csh_readMessageFromQueue(key_t key,struct mymsg * msg,long msgtyp)
{
    /*       printf("\nbegin to read message\n");*/
    int qid;
    int result;
    if((qid=msgget(key,0666|IPC_CREAT))<0)
    {
        perror("msgget");
        exit(1);
    }
    msgrcv(qid,msg,sizeof(struct mymsg),msgtyp,0);
    /*	printf("\nend read message.\n");*/
}


