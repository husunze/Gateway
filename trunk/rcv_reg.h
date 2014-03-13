#ifndef RCV_REG_H_INCLUDED
#define RCV_REG_H_INCLUDED


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
#include<error.h>
#include"AESmain.h"
#include"mysql.h"
#include "error.h"
#include "config.h"

void rcv_reg_run(){
    int iServerActive,iIncomingBytes=1;
    int iSocketFD,iConnectedFD;
    int qid,count;
    pid_t pid_tChildPid;
    char buffer[1024];
    int i,j;
    int m;
    char type[11];
    int socklen_tClientLen;
    struct sockaddr_in sockaddr_inClientAddress;
    struct sockaddr_in sockaddr_inServerAddress;
    key_t key;
    char IP[20];
    char in[16];
    char out[16];
    char *skey;
    char *logfile = "rcv_reg.txt";
    struct mymsg msg1;
    /*if(argc !=2)
    {
    	printf("Usage:\n");
    	printf("./server[port number]\n");
    	exit(1);
    }*/
    if((iSocketFD = socket(AF_INET,SOCK_STREAM,0))<0)
    {
        char *errormsg = "socket error !";
        log(logfile, strlen(logfile), errormsg, strlen(errormsg));
        printf("socket error !\n");
        exit(1);
    }
    memset(&sockaddr_inServerAddress,0,sizeof(sockaddr_inServerAddress));
    sockaddr_inServerAddress.sin_family=AF_INET;
    sockaddr_inServerAddress.sin_addr.s_addr=htonl(INADDR_ANY);
    sockaddr_inServerAddress.sin_port=htons(RCV_REG_PORT);


    if(bind(iSocketFD,(struct sockaddr *)&sockaddr_inServerAddress,
            sizeof(sockaddr_inServerAddress))<0)
    {
        char *errormsg = "bind error !";
        log(logfile, strlen(logfile), errormsg, strlen(errormsg));
        printf("bind error !\n");
        exit(1);
    }

    if(listen(iSocketFD,3)<0)
    {
        char *errormsg = "lister error!";
        log(logfile, strlen(logfile), errormsg, strlen(errormsg));
        printf("listen error ! \n");
        exit(1);
    }
    key=ftok(".",'K');//消息一律投到主文件夹的消息队列
    if((qid=msgget(key,IPC_CREAT|0666))==-1)
    {
        char *errormsg = "msgget!";
        log(logfile, strlen(logfile), errormsg, strlen(errormsg));
        perror("msgget");
        exit(1);
    }
    printf("qid:%d\n",qid);
    iServerActive = 1;
    while(iServerActive)
    {
        socklen_tClientLen=sizeof(sockaddr_inClientAddress);
        if((iConnectedFD = accept(iSocketFD,
                                  (struct sockaddr *)&sockaddr_inClientAddress,
                                  &socklen_tClientLen))<0)
        {
            char *errormsg = "accept error !!";
            log(logfile, strlen(logfile), errormsg, strlen(errormsg));
            printf("accept error !\n");
            exit(1);
            close(socket);
        }
        //这个地方解析出IP
        strcpy(IP,inet_ntoa(sockaddr_inClientAddress.sin_addr));
    //    IP=inet_ntoa(sockaddr_inClientAddress.sin_addr);
        log(logfile, strlen(logfile), IP, strlen(IP));
        printf("Connect from %s\n",IP);
        memset(msg1.msg_buf,0,512);
        if(iIncomingBytes=read(iConnectedFD,msg1.msg_buf,
                               512)>0)
        {
            log(logfile, strlen(logfile), msg1.msg_buf, 512);
            printf("消息内容：");
            for(i=0;i<512;i++)
                printf("%c",msg1.msg_buf[i]);
            printf("\n");
//            for(i=strlen(msg1.msg_buf);i<512;i++)
//                msg1.msg_buf[i]='#';
            //这个地方解密,首先要验证IP是否为正确的IP
            skey=IP_find_key_again(IP);
            if(skey==NULL)
            {
                printf("unsafe message!");
                continue;
            }
            printf("从localdb中找到的SKEY=%s\n",skey);

            //解密
            int z;
            for(i=0;i<32;i++)
            {
                for(j=0;j<16;j++)
                {
                    in[j]=msg1.msg_buf[i*16+j];
                }
//                printf("%d\n",i);
//                for(z=0;z<16;z++)
//                    printf("%c",in[z]);
//                printf("\n");
                decrpt(in,skey,out);
//                printf("after:%d\n",i);
                for(j=0;j<16;j++)
                {
                    msg1.msg_buf[i*16+j]=out[j];
                }
            }
            printf("xiaoxi ceshi wanbi\n");
            printf("jie mi zhi hou消息内容：");
            for(i=0;i<512;i++)
                printf("%c",msg1.msg_buf[i]);
            printf("\n");
            msg1.msg_types=1;
//验证IP，确认消息
            for(i=0;i<20+strlen(IP);i++)
            {
                if(msg1.msg_buf[i]!=IP[i])
                    break;
            }
            printf("%d\n",i);
            if(i<strlen(IP))
            {
                continue;
            }
            printf("这是可靠消息！\n");
            char *msg = "Right message";
            log(logfile, strlen(logfile), msg, strlen(msg));
            count=msgsnd(qid,&msg1,sizeof(msg1.msg_buf),0);
            if(count<0)
            {
                printf("mssage send error,count=%d!\n",count);
                exit(1);
            }
            printf("send msssage ok ! \n");
//            printf("message text ==> \n");
//            for(i=0;i<512;i++)
//            {
//                printf("%c",msg1.msg_buf[i]);
//            }
//            printf("\n");

        }
        close(socket);
    }
    close(iSocketFD);
}

#endif // RCV_REG_H_INCLUDED
