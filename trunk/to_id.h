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
#define MAX  512



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
        sendtowindowsto_id(pmsg.msg_buf);
        in("id 74\n");
    }/*end while*/
    return 0;
}




#endif // TO_ID_H_INCLUDED
