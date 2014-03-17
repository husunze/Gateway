/*
 * id_to_ip.c
 *
 *  Created on: 2013年8月13日
 *      Author: oracle
 */

#include "id_to_ip.h"
char *idToIp(int id,char ip_result[])
{
    long sqlid;
    int i;
    key_t key_of_sql_id;
    key_t key_sql_pool;
    key_t key_sql_result;
    struct mymsg sqltype;
    struct mymsg tempmsg;
    char *select_ip = "select ip from machineid where id=%d;";
    char send[512];
    char true_sql[512];
    int qid;
    char len[20];
    printf("id:%d\n",id);
    sprintf(true_sql,select_ip,id);
    printf("true_sql:%s\n",true_sql);
    key_of_sql_id = ftok(".",'w');
    key_sql_pool = ftok(".",'n');
    csh_readMessageFromQueue(key_of_sql_id,&sqltype,0);
    sqlid=atol(sqltype.msg_buf);
    printf("I get the sqlid:%d\n",sqlid);
    sprintf(send,"%010ld0000000001%010d%s",sqlid,strlen(true_sql),true_sql);
    printf("messge :%s\n",send);
    strcpy(tempmsg.msg_buf,send);
    tempmsg.msg_types=1;
    /*	qid=msgget(key_sql_pool,0666|IPC_CREAT);
    	msgsnd(qid,&tempmsg,sizeof(tempmsg),0);*/
    printf("send msg and ask the ip:\n");
    csh_sendMessageToQueue(key_sql_pool,0,&tempmsg);
    /*	printf("\n=================");*/
    /*	printf("\nsend to sql pool :%s",tempmsg.msg_buf);*/
    key_sql_result=ftok(".",'p');
    memset(tempmsg.msg_buf,0,512);
    printf("I need ip :\n");//这个地方  fromdp.c 应该输入13 172.18.55.237
    csh_readMessageFromQueue(key_sql_result,&tempmsg,sqlid);
    printf("I get message.\n");
    /*	printf("\n_----%s",tempmsg.msg_buf);*/
    for(i=20; i<30; i++)
    {
        len[i-20]=tempmsg.msg_buf[i];
    }
    memset(ip_result,0,20);
    for(i=30; i<(30+atoi(len)); i++)
    {
        ip_result[i-30]=tempmsg.msg_buf[i];
    }
    printf("ip:%s\n",ip_result);
    /*	printf("\nip result is :%s\n",ip_result);     */
}


