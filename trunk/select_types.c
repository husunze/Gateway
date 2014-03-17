/*
 * select_types.c
 *
 *  Created on: 2013年8月13日
 *      Author: oracle
 */

#include "select_types.h"

void select_type2_byname(char type_name[],struct pathtype* yourtype)
{
    long sqlid;
    int i;
    key_t key_of_sql_id;
    key_t key_sql_pool;
    key_t key_sql_result;
    struct mymsg sqltype;
    struct mymsg tempmsg;
    char *select_ip = "select source, destination1,destination2 from type2 where type='%s';";
    char send[512];
    char true_sql[512];
    int qid;
    char len[20];
    int start;
    char source_id[20];
    char destination_id1[20];
    char destination_id2[20];
    int num_source_id,num_destination_id1,num_destination_id2;
    memset(yourtype,0,sizeof(yourtype));
    sprintf(true_sql,select_ip,type_name);
    key_of_sql_id = ftok(".",'w');
    key_sql_pool = ftok(".",'n');
    csh_readMessageFromQueue(key_of_sql_id,&sqltype,0);
    sqlid=atol(sqltype.msg_buf);
    sprintf(send,"%010ld0000000003%010d%s",sqlid,strlen(true_sql),true_sql);
    strcpy(tempmsg.msg_buf,send);
    tempmsg.msg_types=1;
    csh_sendMessageToQueue(key_sql_pool,0,&tempmsg);
    /* printf("\n=====send sql string to snd_sql\33[33 OK \33[0m! ============");*/
    /*  printf("\nsend to sql string pool :%s",tempmsg.msg_buf);*/
    key_sql_result=ftok(".",'p');
    memset(tempmsg.msg_buf,0,512);
    csh_readMessageFromQueue(key_sql_result,&tempmsg,sqlid);
    /* printf("\nrcv one message :->%s",tempmsg.msg_buf);*/
    /*解析source_id*/
    start = 20;
    memset(len,0,20);
    for(i=start; i<start+10; i++)
    {
        len[i-start]=tempmsg.msg_buf[i];
    }
    start = start + 10;
    memset(source_id,0,20);
    for(i=start; i<(start+atoi(len)); i++)
    {
        source_id[i-start]=tempmsg.msg_buf[i];
    }
    /*解析destination_id1*/
    start = start + atoi(len);
    memset(len,0,20);
    for(i=start; i<start+10; i++)
    {
        len[i-start]=tempmsg.msg_buf[i];
    }

    start = start + 10;
    memset(destination_id1,0,20);
    for(i=start; i<(start+atoi(len)); i++)
    {
        destination_id1[i-start]=tempmsg.msg_buf[i];
    }

    /*解析destination_id2*/
    start = start + atoi(len);
    memset(len,0,20);
    for(i=start; i<start+10; i++)
    {
        len[i-start]=tempmsg.msg_buf[i];
    }

    start = start + 10;
    memset(destination_id2,0,20);
    for(i=start; i<(start+atoi(len)); i++)
    {
        destination_id2[i-start]=tempmsg.msg_buf[i];
    }
    /*     printf("\ndecode result:[%s|%s|%s]\n",source_id,destination_id1,destination_id2);*/
    /*set the decode value to the struct*/

    strcpy(yourtype->type_name,type_name);
    idToIp(atoi(source_id),yourtype->source_ip);
    idToIp(atoi(destination_id1),yourtype->destination_ip1);
    idToIp(atoi(destination_id2),yourtype->destination_ip2);
    /*end of fill the struct*/
    printf("\nthe result of select %s is :[%s|%s|%s|%s]\n",type_name,yourtype->type_name,yourtype->source_ip,yourtype->destination_ip1,yourtype->destination_ip2);

}


void select_type1_byname(char type_name[],struct pathtype* yourtype)
{
    long sqlid;
    int i;
    key_t key_of_sql_id;
    key_t key_sql_pool;
    key_t key_sql_result;
    struct mymsg sqltype;
    struct mymsg tempmsg;
    char *select_ip = "select source, destination from type1 where type='type%s';";
    char send[512];
    char true_sql[512];
    int qid;
    char len[20];
    int start;
    char source_id[20];
    char destination_id1[20];
    char destination_id2[20];
    int num_source_id,num_destination_id1,num_destination_id2;
    memset(yourtype,0,sizeof(yourtype));
    sprintf(true_sql,select_ip,type_name);
    printf("ask the type:\n ");
    key_of_sql_id = ftok(".",'w');
    key_sql_pool = ftok(".",'n');
    csh_readMessageFromQueue(key_of_sql_id,&sqltype,0);
    sqlid=atol(sqltype.msg_buf);
    sprintf(send,"%010ld0000000002%010d%s",sqlid,strlen(true_sql),true_sql);
    printf("The message that i send for type:%s\n",send);
    strcpy(tempmsg.msg_buf,send);
    tempmsg.msg_types=1;
    csh_sendMessageToQueue(key_sql_pool,0,&tempmsg);
    printf("I have send message !\n");
    /*    printf("\n=====send sql string to snd_sql OK ! ============");*/
    /*    printf("\nsend to sql string pool :%s",tempmsg.msg_buf);*/
    key_sql_result=ftok(".",'p');
    memset(tempmsg.msg_buf,0,512);
    printf("read message from dp!\n");
    csh_readMessageFromQueue(key_sql_result,&tempmsg,sqlid);
    printf("I have recive the message:%s\n",tempmsg.msg_buf);
    /*  printf("\nrcv one message :->%s",tempmsg.msg_buf);*/
    /*h'#f~^~Psource_id*/
    start = 20;
    memset(len,0,20);
    for(i=start; i<start+10; i++)
    {
        len[i-start]=tempmsg.msg_buf[i];
    }
    start = start + 10;
    memset(source_id,0,20);
    for(i=start; i<(start+atoi(len)); i++)
    {
        source_id[i-start]=tempmsg.msg_buf[i];
    }
    printf("I have get the source id:%s\n",source_id);
    /*h'#f~^~Pdestination_id1*/
    start = start + atoi(len);
    memset(len,0,20);
    for(i=start; i<start+10; i++)
    {
        len[i-start]=tempmsg.msg_buf[i];
    }

    start = start + 10;
    memset(destination_id1,0,20);
    for(i=start; i<(start+atoi(len)); i++)
    {
        destination_id1[i-start]=tempmsg.msg_buf[i];
    }

    /*set the decode value to the struct*/

    strcpy(yourtype->type_name,type_name);
    idToIp(atoi(source_id),yourtype->source_ip);
    idToIp(atoi(destination_id1),yourtype->destination_ip1);
    /*end of fill the struct*/
    printf("\nthe result of select %s is :[%s|%s|%s|%s]\n",type_name,yourtype->type_name,yourtype->source_ip,yourtype->destination_ip1,yourtype->destination_ip2);

}


