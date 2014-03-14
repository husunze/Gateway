#ifndef JUDGE1_H_INCLUDED
#define JUDGE1_H_INCLUDED

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
#include<unistd.h>
#include"AESmain.h"
#include"mysql.h"
#include "error.h"
#include "config.h"
void judge1_run()
{

    /* char *type_p[]={"type1###############","type2###############","type3###############","type4###############","type5###############","type6###############","type7###############","type8###############","type9###############","type10##############","type11##############","type12##############"};
     */
    int qid1,qid2,qid3;
    int len;
    int i,j;
    int m=0,n=0;
    key_t mykey1,mykey2,mykey3;
    struct mymsg pmsg;
    struct message msgs;
    int i_type;
    char s_type[20];
    mykey1=ftok(".",'a'); /*from font*/
    mykey2=ftok(".",'h'); /*to 1:2 deal*/
    mykey3=ftok(".",'g'); /*to 1:1 deal*/
    if((qid1=msgget(mykey1,IPC_CREAT|0666))<0)
    {
        perror("msgget");
        exit(1);
    }
    printf("I'm going to get the message!\n");
    for(;;)
    {
        len=msgrcv(qid1,&pmsg,BUFSZ,0,0);
        if(len>0)
        {
            pmsg.msg_buf[len]='\0';
              printf("message text:%s\n",pmsg.msg_buf);
            for(i=160; i<180; i++)
            {
                msgs.type[i-160]=pmsg.msg_buf[i];
                msgs.type[20]='\0';
            }
            judge_type_byname(msgs.type,s_type);
            i_type = atoi(s_type);/*
 if(strcmp(msgs.type,type_p[6])==0||strcmp(msgs.type,type_p[7])==0||strcmp(msgs.type,type_p[8])==0||strcmp(msgs.type,type_p[9])==0||strcmp(msgs.type,type_p[10])==0||strcmp(msgs.type,type_p[11])==0)*/
            printf("================>i_type = %d\n;",i_type);
            if(i_type==2)
            {
                sprintf(pmsg.msg_buf,"%s\n",pmsg.msg_buf);
                len=sizeof(pmsg.msg_buf);
               //   printf("now in type7_12!");
                if((qid2=msgget(mykey2,IPC_CREAT|0666))<0)
                {
                    perror("msgget");
                    exit(1);
                }

                if((msgsnd(qid2,&pmsg,len,0))<0)
                {
                    perror("msgsnd");
                    exit(1);
                }
                  printf("successfully send a message to the queue2:%d\n",qid2);
            }/*
 else if(strcmp(msgs.type,type_p[0])==0||strcmp(msgs.type,type_p[1])==0||strcmp(msgs.type,type_p[2])==0||strcmp(msgs.type,type_p[3])==0||strcmp(msgs.type,type_p[4])==0||strcmp(msgs.type,type_p[5])==0)*/
            else if(i_type == 1)
            {
                sprintf(pmsg.msg_buf,"%s\n",pmsg.msg_buf);
                len=sizeof(pmsg.msg_buf);
                /*  printf("now in type1-6!");*/
                if((qid3=msgget(mykey3,IPC_CREAT|0666))<0)
                {
                    perror("msgget");
                    exit(1);
                }

                if((msgsnd(qid3,&pmsg,len,0))<0)
                {
                    perror("msgsnd");
                    exit(1);
                }
                  printf("successfully send a message to the queue3:%d\n",qid3);
            }
        }
        else if(len<0)
        {
            printf("error\n");
            perror("rcvmsg");
            exit(1);
        }
    }
    system("ipcs -q");
    exit(0);
}


#endif // JUDGE1_H_INCLUDED
