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

int socket_fd;
struct sockaddr_in sockaddr_inServerAddress;

//void to_font_sendtowindows(char* data);

void to_font_run(int argc,char *argv[])
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
        to_font_sendtowindows(pmsg.msg_buf);
    }/*end while*/
    //return 0;
}

void to_font_sendtowindows(char* data)
{
    int i=80;
    char dis[20];
    char *skey;
    char in[16];
    char out[16];
    int j;
    for(i; i<=99; i++)
    {
        printf("%c",data[i]);
        if(data[i]!='#')
        {
            dis[i-80]=data[i];
        }
        else
        {
            break;
        }
    }
    dis[i-80]='\0';
    skey=IP_find_key(dis);
    printf("key:%s\n",skey);
    for(i=0;i<32;i++)
    {

        for(j=0;j<16;j++)
        {
            in[j]=data[i*16+j];
        }
        encrpt(in,skey,out);
        for(j=0;j<16;j++)
        {
            data[i*16+j]=out[j];
        }
    }
    printf("the distinatino ip is %s",dis);
    memset(&sockaddr_inServerAddress,0,sizeof(sockaddr_inServerAddress));

    sockaddr_inServerAddress.sin_family=AF_INET;
    sockaddr_inServerAddress.sin_addr.s_addr=inet_addr(dis);
    sockaddr_inServerAddress.sin_port=htons(8886);


    if((socket_fd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket error\n");
        exit(1);
    }
    if(connect(socket_fd,(struct sockaddr *)&sockaddr_inServerAddress,sizeof(sockaddr_inServerAddress))!=0)
    {
        printf("connect error !\n");
        close(socket_fd);
        exit(1);
    }
    if(send(socket_fd,data,strlen(data),0)==-1)
    {
        printf("send error!\n");
        exit(1);
    }
    close(socket_fd);

}



#endif // TO_FONT_H_INCLUDED
