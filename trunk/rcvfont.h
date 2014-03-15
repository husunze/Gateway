#ifndef RCVFONT_H_INCLUDED
#define RCVFONT_H_INCLUDED
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include "sql.h"
#include "select_types.h"

void rcvfont_run()
{
    /*
    	char *type_p[]={"type1###############","type2###############","type3###############","type4###############","type5###############","type6###############"};
    	int typestart[6]={1,2,0,2,0,1};
    	char *address[]={"192.168.5.97########","192.168.5.86########","192.168.5.84########"};
    */
    char rout_p[21]/*="192.168.5.85########"*/;
    char s[8][20],b[8][20];
    char  buf[300];
    struct mymsg pmsg,tempmsg,sqlmsg;
    key_t key;
    char select_temp[21];
    char temp[21];
    int i,j,k,m;
    char csh_temp[21];
    memset(csh_temp,0,21);
    struct pathtype pathtype1;
    memset(rout_p,0,21);
    idToIp(0,rout_p);//为啥是这样的？这个地方应该是指的本地IP
    for(k=19; k>=strlen(rout_p); k--)
    {
        rout_p[k]='#';
        putchar('#');
    }
    printf("----------->the rout ip is %s\n",rout_p);
    for(;;)
    {
        //这个地方写统计代码，用来统计交易类型
        //
        //
        //
        /*从g队列中取出一条消息来*/
        key=ftok(".",'g');
        readMessageFromQueue(key,&pmsg,0);/*0表示读不到就阻塞*/
        printf("dudaodexiaoxineirongwei:%s\n",pmsg.msg_buf);
        /*把消息发送到监控和数据库*/
        key=ftok(".",'b');
        printf(" I need send message to dp anf windows!\n");

        sendMessageToQueue(key,0,&pmsg);
        printf("I had send message to windows!\n");
        sendinsertsql(pmsg);
        printf("I have send message to dp!\n");
        /*key=ftok(".",'n');
        readMessageFromQueue(key,&sqlmsg,0);*/
        // printf("发送到数据库的sql语句为：%s\n",sqlmsg.msg_buf);


        //key=ftok(".",'e');
        //sendMessageToQueue(key,0,&pmsg);

        /*修改源和目的的IP地址*/
        for(i=0; i<20; i++)
        {
            temp[i]=pmsg.msg_buf[i+160];
        }
        temp[i]='\0';
        printf("temp=%s\n",temp);/*
    for(i=0;i<6;i++){
    	if(strcmp(temp,type_p[i])==0){
                printf("-----------kaishitype-----------%d",typestart[i]);
    		strcpy(temp,address[typestart[i]]);
                printf("----------mude ________-%s",temp);
       		for(j=0;j<20;j++){
   			pmsg.msg_buf[60+j]=rout_p[j];
	   		pmsg.msg_buf[80+j]=	temp[j];
    		}
    		break;
    	}
    }*/
        memset(select_temp,0,21);
        for(m=0; m<20; m++)
        {
            if(temp[m]!='#')
            {
                select_temp[m]=temp[m];
            }
            else
            {
                break;
            }
        }
        printf("the type you want to select is:%s\n",select_temp);
        select_type1_byname(select_temp,&pathtype1);
        memset(csh_temp,0,21);
        strcpy(csh_temp,pathtype1.destination_ip1);/*注意i的值在其它地方不能改的*/
        for(k=19; k>=strlen(csh_temp); k--)
        {
            csh_temp[k]='#';
        }
        printf("in rcvfont the csh_temp value is :%s\n",csh_temp);
        for(j=0; j<20; j++)
        {
            pmsg.msg_buf[60+j]=rout_p[j];/*改变源*/
            pmsg.msg_buf[80+j]=csh_temp[j];/*改变目地*/
        }

        printf("sent to monitor the second time .%s\n",pmsg.msg_buf);
        sendupdatesql(pmsg);
        key=ftok(".",'b');
        sendMessageToQueue(key,0,&pmsg);
        //key=ftok(".",'n');
        //sendMessageToQueue(key,0,&sqlmsg);
        key=ftok(".",'c');
        sendMessageToQueue(key,0,&pmsg);
        printf("++++++++++++++++++++++++++++++\n");
    }
}


#endif // RCVFONT_H_INCLUDED
