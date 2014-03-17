#ifndef TO_ID_H_INCLUDED
#define TO_ID_H_INCLUDED
#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/ipc.h>
#include<arpa/inet.h>
#include<sys/msg.h>
#include"error.h"
#include "mysql.h"
#include "AESmain.h"
#include "config.h"

int socket_fd;
struct sockaddr_in sockaddr_inServerAddress;
//void sendtowindows(char* data);
void to_id_run(int argc,char *argv[])
{

    int qid;
    key_t key;
    int len;
    struct mymsg pmsg;
    key=ftok(".",'z');
    printf("key=%x\n",key);
    if((qid=msgget(key,IPC_CREAT|0666))==-1)
    {
        perror("msgget error!");
        exit(1);
    }
    printf("qid=%d\n",qid);
    in("id 47\n");
    for(;;)
    {
        in("id 50\n");
        len=msgrcv(qid,&pmsg,sizeof(pmsg.msg_buf),0,0);
        printf("%d\n",len);
        in("id 53\n");
        if(len<0)
        {
            perror("msgrcv error!");
            in("id 57\n");
            exit(1);
        }
        else if(len==0)
        {
            printf("no date in quene!");
            in("id 63\n");
            exit(1);
        }
        else
        {
            printf("i will send a message to windows ,the message is %s\n",pmsg.msg_buf);
            printf("_________________________________\n");
            in("id 53\n");
        }
        printf("get in 65\n");
        to_id_sendtowindows(pmsg.msg_buf);
        in("id 74\n");
    }/*end while*/
    //return 0;
}


void to_id_sendtowindows(char* data)
{
    int i,j;
    char dis[20];
    char in[16];
    char out[16];
    char *k;
    for(i=0; i<20; i++)
    {
        if(data[i]!='#')
        {
            dis[i]=data[i];
        }
        else
        {
            break;
        }
    }
    dis[i]='\0';
    printf("the distinatino ip is %s",dis);
    k=IP_find_key(dis);
    printf("key:%s\n",k);
    for(i=0;i<32;i++)
    {

        for(j=0;j<16;j++)
        {
            in[j]=data[i*16+j];
        }
        encrpt(in,k,out);
        for(j=0;j<16;j++)
        {
            data[i*16+j]=out[j];
        }
    }
    memset(&sockaddr_inServerAddress,0,sizeof(sockaddr_inServerAddress));

    sockaddr_inServerAddress.sin_family=AF_INET;
    sockaddr_inServerAddress.sin_addr.s_addr=inet_addr(dis);
    sockaddr_inServerAddress.sin_port=htons(4060);
    if((socket_fd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket error\n");
        exit(1);
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
    printf("send successfully!\n");
    close(socket_fd);

}


#endif // TO_ID_H_INCLUDED
