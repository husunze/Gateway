#ifndef TO_MONITOR_H_INCLUDED
#define TO_MONITOR_H_INCLUDED

#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/ipc.h>
#include<arpa/inet.h>
#include<sys/msg.h>
#include<config.h>
#include"error.h"

#define MAX  512


int socket_fd;
struct sockaddr_in sockaddr_inServerAddress;
void sendtowindows(char* data);
void to_monitor_run()
{

    int qid;
    key_t key;
    int len;
    struct mymsg pmsg;
    in("minitor 29\n");
    if(argc!=3)
    {
        printf("Usage:\n");
        printf("TcpEchoClient.exe <ipaddress><protnum>\n");
        exit(1);
    }
    in("minitor 36\n");
    memset(&sockaddr_inServerAddress,0,sizeof(sockaddr_inServerAddress));

    sockaddr_inServerAddress.sin_family=AF_INET;
    sockaddr_inServerAddress.sin_addr.s_addr=inet_addr(argv[1]);
    sockaddr_inServerAddress.sin_port=htons(atoi(argv[2]));
    in("minitor 44\n");
    key=ftok(".",'b');
    printf("key=%x\n",key);
    if((qid=msgget(key,IPC_CREAT|0666))==-1)
    {
        perror("msgget error!");
        exit(1);
    }
    printf("qid=%d\n",qid);
   in("minitor 53\n");
    while(1)
    {
        in("minitor 56\n");
        len=msgrcv(qid,&pmsg,sizeof(pmsg.msg_buf),0,0);
          in("minitor 58\n");
        if(len<0)
        {
            in("minitor 61\n");
            perror("msgrcv error!");
            exit(1);
        }
        else if(len==0)
        {
            in("minitor 67\n");
            printf("no date in quene!");
            exit(1);
        }

        else
        {
              in("minitor 74n");
            printf("i will send a message to monitor ,the message is %s\n",pmsg.msg_buf);
            printf("_________________________________\n");
        }
          in("minitor 78\n");
        sendtowindows(pmsg.msg_buf);
          in("minitor 80\n");
        sleep(2);


    }/*end while*/
    return 0;
}


void sendtowindows(char* data)
{

    in("monitoe 92\n");
    if((socket_fd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        in("monitoe 95\n");
        perror("socket error\n");
        exit(1);
    }
    in("monitoe 99\n");
    if(connect(socket_fd,(struct sockaddr *)&sockaddr_inServerAddress,sizeof(sockaddr_inServerAddress))!=0)
    {
        in("monitoe 102\n");
        printf("connect error !\n");
        close(socket_fd);
        exit(1);
    }

#endif // TO_MONITOR_H_INCLUDED
