#ifndef SND_SQL_H_INCLUDED
#define SND_SQL_H_INCLUDED

#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/ipc.h>
#include<arpa/inet.h>
#include<sys/msg.h>
#include "config.h"



void snd_sql_run(){
    int qid;
    key_t key;
    int len;
    struct mymsg pmsg;
    printf("snd_sql started.\n");
    key=ftok(".",'n');
    printf("key=%x\n",key);
    if((qid=msgget(key,IPC_CREAT|0666))==-1)
    {
        perror("msgget error!");
        exit(1);
    }
    printf("qid=%d\n",qid);

    while(1)
    {
        len=msgrcv(qid,&pmsg,sizeof(pmsg.msg_buf),0,0);
        if(len<0)
        {
            perror("msgrcv error!");
        }
        else if(len==0)
        {
            printf("no date in quene!");
        }

        else
        {
            printf("i will send a message to db ,the message is %s\n",pmsg.msg_buf);
            printf("_________________________________\n");
        }
        snd_sql_sendtowindows(pmsg.msg_buf);
    }/*end while*/
    return 0;

}

void snd_sql_sendtowindows(char* data)
{
    int socket_fd;
    struct sockaddr_in sockaddr_inServerAddress;
    memset(&sockaddr_inServerAddress,0,sizeof(sockaddr_inServerAddress));
    sockaddr_inServerAddress.sin_family=AF_INET;
    sockaddr_inServerAddress.sin_addr.s_addr=inet_addr(DATABASEIP);
    sockaddr_inServerAddress.sin_port=htons(atoi("1234"));
    if((socket_fd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket error\n");
    }
    if(connect(socket_fd,(struct sockaddr *)&sockaddr_inServerAddress,sizeof(sockaddr_inServerAddress))!=0)
    {
        printf("connect error !\n");
        close(socket_fd);
    }
    if(send(socket_fd,data,strlen(data),0)==-1)
    {
        printf("send error!\n");
    }
    close(socket_fd);

}

#endif // SND_SQL_H_INCLUDED
