#ifndef RCV_SQLRES_H_INCLUDED
#define RCV_SQLRES_H_INCLUDED
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<netdb.h>
#include "config.h"

void rcv_sqlRes_run(){
    struct mymsg msg1;
    int iServerActive,iIncomingBytes=1;
    int iSocketFD,iConnectedFD;
    int qid,count;
    pid_t pid_tChildPid;
    char buffer[1024];
    int i ;
    int m;
    char type[11];
    int socklen_tClientLen;
    struct sockaddr_in sockaddr_inClientAddress;
    struct sockaddr_in sockaddr_inServerAddress;
    key_t key;
    /*if(argc !=2)
    {
    	printf("Usage:\n");
    	printf("./server[port number]\n");
    	exit(1);
    }*/
    if((iSocketFD = socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("socket error !\n");
        exit(1);
    }
    memset(&sockaddr_inServerAddress,0,sizeof(sockaddr_inServerAddress));
    sockaddr_inServerAddress.sin_family=AF_INET;
    sockaddr_inServerAddress.sin_addr.s_addr=htonl(INADDR_ANY);
    sockaddr_inServerAddress.sin_port=htons(RCV_SQL_RES_PORT);


    if(bind(iSocketFD,(struct sockaddr *)&sockaddr_inServerAddress,
            sizeof(sockaddr_inServerAddress))<0)
    {
        printf("bind error !\n");
        exit(1);
    }

    if(listen(iSocketFD,3)<0)
    {
        printf("listen error ! \n");
        exit(1);
    }
    key=ftok(".",'p');
    if((qid=msgget(key,IPC_CREAT|0666))==-1)
    {
        perror("msgget");
        exit(1);
    }
    iServerActive = 1;
    while(iServerActive)
    {
        socklen_tClientLen=sizeof(sockaddr_inClientAddress);
        if((iConnectedFD = accept(iSocketFD,
                                  (struct sockaddr *)&sockaddr_inClientAddress,
                                  &socklen_tClientLen))<0)
        {
            printf("accept error !\n");
            exit(1);
            close(socket);
        }
        printf("Connect from %s\n",
               inet_ntoa(sockaddr_inClientAddress.sin_addr));
        memset(msg1.msg_buf,0,512);
        if(iIncomingBytes=read(iConnectedFD,msg1.msg_buf,
                               512)>0)
        {
            printf("%s\n",msg1.msg_buf);
            for(m=0; m<10; m++)
            {

                type[m]=msg1.msg_buf[m];
            }
            type[10]='\0';
            msg1.msg_types=atol(type);
            printf("key=%x the quene is p\n",key);
            printf("qid=%d   ssi\n",qid);
            /*strcpy(msg1.mtext,buffer);*/

            count=msgsnd(qid,&msg1,sizeof(msg1.msg_buf),0);
            if(count<0)
            {
                printf("mssage send error,count=%d!",count);
                exit(1);
            }

            printf("send msssage ok ! ");
            printf("message text ==> %s\n",msg1.msg_buf);
        }
        close(socket);
    }
    close(iSocketFD);
}

#endif // RCV_SQLRES_H_INCLUDED
