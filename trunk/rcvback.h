#ifndef RCVBACK_H_INCLUDED
#define RCVBACK_H_INCLUDED
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include "sql.h"
#include "select_types.h"
#include "config.h"

void rcvback_run(int argc, char *argv[])
{
    /*
    char *type_p[]={"type1###############","type2###############","type3###############","type4###############","type5###############","type6###############"};
    	int typestart[6]={1,2,0,2,0,1};
    	int returntype[6]={0,0,1,1,2,2};
    	char *address[]={"192.168.5.97########","192.168.5.86########","192.168.5.84########"};*/
    char rout_p[21]/*="192.168.5.85########"*/;
    char s[8][20],b[8][20];
    char  buf[300];
    char insertSql[300]="insert into deals ('%s','%s','%s','%s','%s','%s','%s','%s','%s')";
    char updateSql[200]="update deals set SourceId='%s' DestinationId='%s' where DealId='%s'";
    struct mymsg pmsg,tempmsg,sqlmsg;
    key_t key;
    char temp[21];
    char select_type[21];
    int m, i,j,start,k;
    struct pathtype pathtype1;
    memset(rout_p,0,21);
    idToIp(0,rout_p);
    for(k=19; k>=strlen(rout_p); k--)
    {
        rout_p[k]='#';
    }
    printf("the rout ip is :%s\n",rout_p);
    for(;;)
    {
        /*从h队列中取出一条消息来*/
        key=ftok(".",'j');
        readMessageFromQueue(key,&pmsg,0);/*0表示读不到就阻塞*/
        /*把消息发送到监控和数据库*/
        key=ftok(".",'b');
        sendMessageToQueue(key,0,&pmsg);
        sendupdatesql(pmsg);

        for(i=0; i<20; i++)
        {
            temp[i]=pmsg.msg_buf[i+160];
        }
        temp[i]='\0';
        /*修改源和目的的IP地址*/
        /*
            for(start=0;start<6;start++){
            	if(strcmp(temp,type_p[start])==0){
            		break;
            		}
            }*/
        memset(select_type,0,21);
        for(m=0; m<20; m++)
        {
            if(temp[m]!='#')
            {
                select_type[m]=temp[m];
            }
            else
            {
                break;
            }

        }
        select_type1_byname(select_type,&pathtype1);
        /*     strcpy(temp,address[returntype[start]]);*/
        memset(temp,0,21);
        strcpy(temp,pathtype1.source_ip);
        for(m=19; m>=strlen(temp); m--)
        {

            temp[m]='#';
        }
        for(i=0; i<20; i++)
        {
            pmsg.msg_buf[60+i]=rout_p[i];
            pmsg.msg_buf[80+i]=temp[i];
        }
        sendupdatesql(pmsg);
        printf("发送以下消息到数据库和监视器以及C消息队列:%s\n",sqlmsg.msg_buf);
        key=ftok(".",'b');
        sendMessageToQueue(key,0,&pmsg);
        key=ftok(".",'f');
        sendMessageToQueue(key,0,&pmsg);
    }
}



#endif // RCVBACK_H_INCLUDED
