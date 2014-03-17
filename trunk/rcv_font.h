#ifndef RCV_FONT_H_INCLUDED
#define RCV_FONT_H_INCLUDED

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
#include"config.h"

//#include"AESmain.h"
//#include"mysql.h"

#define PORT 8881
struct mymsg msg1;
int rcv_font_run(int argc,char *argv[])
{
    int iServerActive,iIncomingBytes=1;
    int iSocketFD,iConnectedFD;
    int qid,count;
    pid_t pid_tChildPid;
    char buffer[512];
    int i ,j;
    int socklen_tClientLen;
    struct sockaddr_in sockaddr_inClientAddress;
    struct sockaddr_in sockaddr_inServerAddress;
    key_t key;
    char IP[20];
    char *skey;
    char in[16];
    char out[16];
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
    sockaddr_inServerAddress.sin_port=htons(PORT);


    if(bind(iSocketFD,(struct sockaddr *)&sockaddr_inServerAddress,
            sizeof(sockaddr_inServerAddress))<0)
    {
        printf("bind error !\n");
        close(iSocketFD);
        exit(1);
    }

    if(listen(iSocketFD,3)<0)
    {
        printf("listen error ! \n");
        close(iSocketFD);
        exit(1);
    }
    key=ftok(".",'a');
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
            close(socket);
        }
        strcpy(IP,inet_ntoa(sockaddr_inClientAddress.sin_addr));
        //    IP=inet_ntoa(sockaddr_inClientAddress.sin_addr);
        printf("Connect from %s\n",IP);
        memset(buffer,0,512);
        if(iIncomingBytes=read(iConnectedFD,msg1.msg_buf,
                               180)>0)
        {
            skey=IP_find_key(IP);
            printf("从localdb中找到的SKEY=%s\n",skey);

            //解密
            int z;
            /*
            for(i=0;i<32;i++)
            {
                for(j=0;j<16;j++)
                {
                    in[j]=msg1.msg_buf[i*16+j];
                }
                decrpt(in,skey,out);
                for(j=0;j<16;j++)
                {
                    msg1.msg_buf[i*16+j]=out[j];
                }
            }
            msg1.msg_buf[180]='\0';
            printf("xiaoxi ceshi wanbi\n");
            printf("jie mi zhi hou消息内容：");
            */
            for(i=0;i<512;i++)   //config is buf
                printf("%c",msg1.msg_buf[i]);
            msg1.msg_types=1;
            printf("key=%x\n",key);
            printf("qid=%d   ssi\n",qid);
            /*strcpy(msg1.mtext,buffer);*/
            count=msgsnd(qid,&msg1,sizeof(msg1.msg_buf),0);
            if(count<0)
            {
                printf("mssage send error,count=%d!",count);
                exit(1);
            }
            printf("send msssage ok !sfdj lasf ");
            printf("message text:%s:\n",msg1.msg_buf);
        }
        close(socket);
    }
    close(iSocketFD);

}


#endif // RCV_FONT_H_INCLUDED
