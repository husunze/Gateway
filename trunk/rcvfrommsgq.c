/*
 * rcvfrommsgq.c
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */
#include "rcvfrommsgq.h"

void rcvfrommsgq(key_t key, long type, char* sqlRes)
{
    /* char **deal 是用来指向记录查询到的sql语句的内容字符串的*/
    int qid, len;
    int start;/*记录待解析的字符串的起始位置*/
    key_t mykey;
    char getmsg[BUF];
    char length[LEN];
    struct mymsg pmsg;

    mykey = key;

    if ((qid = msgget(key, IPC_CREAT | 0666)) < 0)
    {
        perror("msgget error!");
        exit(1);
    }

    if ((len = msgrcv(qid, &pmsg, BUF, type, 0)) > 0)
    {
        strcpy(sqlRes, pmsg.msg_buf);
    }
    /*
     int i,j;
     for(i=0;i<10;i++)
     length[i] = getmsg[i+10];解析该字符串的有多少个字段
     start=20;字符串的真正内容开始的地方为第20个字符
     for(i=0;i<atoi(length);i++)共需处理的字段个数
     { int len;
     char s[LEN];
     char *data;
     for(j=0;j<10;j++) 具体到某一个字段，取出该字段中该字段的内容的长度
     s[j]=getmsg[start+j];
     len=atoi(s);
     start+=10;记录具体某一字段的数组的长度为10
     data= (char *)malloc(sizeof(char *)*(len+1));
     for(j=0;j<len;j++){将内容存储在data数组中
     data[j]=getmsg[start+j];
     *deal = data;
     }
     free(data);
     start+=len;
     }*/
    return;
}

