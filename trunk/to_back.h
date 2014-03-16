#ifndef TO_BACK_H_INCLUDED
#define TO_BACK_H_INCLUDED
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

void to_back_run()
{

    int qid;
    key_t key;
    int len;
    struct mymsg pmsg;
    /*
     	if(argc!=2)
    {
    	printf("Usage:\n");
    	printf("To_back<protnum>\n");
    	exit(1);
    }

    */
    key=ftok(".",'c');
    printf("key=%x\n",key);
    if((qid=msgget(key,IPC_CREAT|0666))==-1)
    {
        perror("msgget error!");
        exit(1);
    }
    printf("qid=%d\n",qid);

    for(;;)
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




#endif // TO_BACK_H_INCLUDED
