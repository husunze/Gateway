#ifndef TO_FONT_H_INCLUDED
#define TO_FONT_H_INCLUDED
#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/ipc.h>
#include<arpa/inet.h>
#include<sys/msg.h>
#include "mysql.h"
#include "AESmain.h"
#include "config.h"
#define MAX  512


void to_font_run()
{
int qid;
    key_t key;
    int len;
    struct mymsg pmsg;

    /* 	if(argc!=3)
    {
    	printf("Usage:\n");
    	printf("TcpEchoClient.exe <ipaddress><protnum>\n");
    	exit(1);
    }

    memset(&sockaddr_inServerAddress,0,sizeof(sockaddr_inServerAddress));

    sockaddr_inServerAddress.sin_family=AF_INET;
    sockaddr_inServerAddress.sin_addr.s_addr=inet_addr(argv[1]);
    sockaddr_inServerAddress.sin_port=htons(atoi(argv[2]));
    */
    key=ftok(".",'f');
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
            exit(1);
        }
        else if(len==0)
        {
            printf("no date in quene!");
            exit(1);
        }

        else
        {
            printf("i will send a message to windows ,the message is %s\n",pmsg.msg_buf);
            printf("_________________________________\n");
        }
        sendtowindows(pmsg.msg_buf);
    }/*end while*/
    return 0;
}

#endif // TO_FONT_H_INCLUDED
