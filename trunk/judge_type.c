/*
 * judge_type.c
 *
 *  Created on: 2013年8月13日
 *      Author: oracle
 */

#include "judge_type.h"

void judge_type_byname(char type_name[],char result[])
{
    long sqlid;
    int i;
    char temp_result[20];
    int from_type1,from_type2;
    key_t key_of_sql_id;
    key_t key_sql_pool;
    key_t key_sql_result;
    struct mymsg sqltype;
    struct mymsg tempmsg;
    char *select_from_type1 = "select count(*) from type1 where type='type%s';";
    char *select_from_type2 = "select count(*) from type2 where type='type%s';";//这个地方加了一个“type”
    char send[512];
    char true_sql[512];
    int qid;
    char len[20];
    int k;
    char k_temp_type[20];
    memset(k_temp_type,0,20);
    for(k=0; k<=20; k++)
    {
        if(type_name[k]!='#')
        {
            k_temp_type[k] = type_name[k];
        }
        else
        {
            break;
        }
    }
    memset(type_name,0,20);
    strcpy(type_name,k_temp_type);
    key_of_sql_id = ftok(".",'w');
    key_sql_pool = ftok(".",'n');
    key_sql_result=ftok(".",'p');
    /*decode if in table type1*/
    memset(true_sql,0,512);
    sprintf(true_sql,select_from_type1,type_name);
    csh_readMessageFromQueue(key_of_sql_id,&sqltype,0);
    sqlid=atol(sqltype.msg_buf);
    memset(send,0,512);
    sprintf(send,"%010ld0000000001%010d%s",sqlid,strlen(true_sql),true_sql);
    memset(tempmsg.msg_buf,0,512);
    strcpy(tempmsg.msg_buf,send);
    tempmsg.msg_types=1;
    /*	qid=msgget(key_sql_pool,0666|IPC_CREAT);
    	msgsnd(qid,&tempmsg,sizeof(tempmsg),0);*/
    csh_sendMessageToQueue(key_sql_pool,0,&tempmsg);
    printf("\n=================\n");
    printf("\nsend to sql pool :%s\n",tempmsg.msg_buf);
    memset(tempmsg.msg_buf,0,512);
    csh_readMessageFromQueue(key_sql_result,&tempmsg,sqlid);
    printf("\n_----%s\n",tempmsg.msg_buf);
    for(i=20; i<30; i++)
    {
        len[i-20]=tempmsg.msg_buf[i];
    }
    memset(temp_result,0,20);
    for(i=30; i<(30+atoi(len)); i++)
    {
        temp_result[i-30]=tempmsg.msg_buf[i];
    }
    printf("\33[33m select  result1 is :%s\33[0m\n",temp_result);
    from_type1 = atoi(temp_result);

    /*-------------------------------------------------------------------------------*/
    /*decode if in table type2*/
    memset(true_sql,0,512);
    sprintf(true_sql,select_from_type2,type_name);
    csh_readMessageFromQueue(key_of_sql_id,&sqltype,0);
    sqlid=atol(sqltype.msg_buf);
    memset(send,0,512);
    sprintf(send,"%010ld0000000001%010d%s",sqlid,strlen(true_sql),true_sql);
    memset(tempmsg.msg_buf,0,512);
    strcpy(tempmsg.msg_buf,send);
    tempmsg.msg_types=1;
    /*      qid=msgget(key_sql_pool,0666|IPC_CREAT);
            msgsnd(qid,&tempmsg,sizeof(tempmsg),0);*/
    csh_sendMessageToQueue(key_sql_pool,0,&tempmsg);
    printf("\n=================\n");
    printf("\nsend to sql pool :%s\n",tempmsg.msg_buf);
    memset(tempmsg.msg_buf,0,512);
    csh_readMessageFromQueue(key_sql_result,&tempmsg,sqlid);
    printf("\n_----%s\n",tempmsg.msg_buf);
    for(i=20; i<30; i++)
    {
        len[i-20]=tempmsg.msg_buf[i];
    }
    memset(temp_result,0,20);
    for(i=30; i<(30+atoi(len)); i++)
    {
        temp_result[i-30]=tempmsg.msg_buf[i];
    }
    printf("\33[32m select  result2 is :%s \33[0m\n",temp_result);
    from_type2 = atoi(temp_result);

    /*begin to judge the type*/
    *result = 0;
    if(from_type1!=0&&from_type2==0)
    {
        strcpy(result,"1");
    }
    else if(from_type1==0&&from_type2!=0)
    {
        strcpy(result,"2");
    }
    else
    {
        strcpy(result,"-1");
    }
    printf("\33[32m the type is in the table of type%s \33[0m\n",result);
}

