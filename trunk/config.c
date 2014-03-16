#include "config.h"
/*to_font.h*/
int socket_fd;
struct sockaddr_in sockaddr_inServerAddress;

void sendtowindows(char* data)
{
    int i=80;
    char dis[20];
    char *skey;
    char in[16];
    char out[16];
    int j;
    for(i; i<=99; i++)
    {
        printf("%c",data[i]);
        if(data[i]!='#')
        {
            dis[i-80]=data[i];
        }
        else
        {
            break;
        }
    }
    dis[i-80]='\0';
    skey=IP_find_key(dis);
    printf("key:%s\n",skey);
    for(i=0;i<32;i++)
    {

        for(j=0;j<16;j++)
        {
            in[j]=data[i*16+j];
        }
        encrpt(in,skey,out);
        for(j=0;j<16;j++)
        {
            data[i*16+j]=out[j];
        }
    }
    printf("the distinatino ip is %s",dis);
    memset(&sockaddr_inServerAddress,0,sizeof(sockaddr_inServerAddress));
    sockaddr_inServerAddress.sin_family=AF_INET;
    sockaddr_inServerAddress.sin_addr.s_addr=inet_addr(dis);
    sockaddr_inServerAddress.sin_port=htons(8886);

    if((socket_fd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket error\n");
        exit(1);
    }
    if(connect(socket_fd,(struct sockaddr *)&sockaddr_inServerAddress,sizeof(sockaddr_inServerAddress))!=0)
    {
        printf("connect error !\n");
        close(socket_fd);
        exit(1);
    }
    if(send(socket_fd,data,strlen(data),0)==-1)
    {
        printf("send error!\n");
        exit(1);
    }
    close(socket_fd);

}

/*to_id.h*/
void sendtowindowsto_id(char* data)
{
    int i,j;
    char dis[20];
    char in[16];
    char out[16];
    char *k;
    for(i=0; i<20; i++)
    {
        if(data[i]!='#')
        {
            dis[i]=data[i];
        }
        else
        {
            break;
        }
    }
    dis[i]='\0';
    printf("the distinatino ip is %s",dis);
    k=IP_find_key(dis);
    printf("key:%s\n",k);
    for(i=0;i<32;i++)
    {

        for(j=0;j<16;j++)
        {
            in[j]=data[i*16+j];
        }
        encrpt(in,k,out);
        for(j=0;j<16;j++)
        {
            data[i*16+j]=out[j];
        }
    }
    memset(&sockaddr_inServerAddress,0,sizeof(sockaddr_inServerAddress));

    sockaddr_inServerAddress.sin_family=AF_INET;
    sockaddr_inServerAddress.sin_addr.s_addr=inet_addr(dis);
    sockaddr_inServerAddress.sin_port=htons(4060);
    if((socket_fd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket error\n");
        exit(1);
    }
    if(connect(socket_fd,(struct sockaddr *)&sockaddr_inServerAddress,sizeof(sockaddr_inServerAddress))!=0)
    {
        printf("connect error !\n");
        close(socket_fd);
    }
    if(send(socket_fd,data,strlen(data),0)==-1)
    {
        printf("send error!\n");
    }
    printf("send successfully!\n");
    close(socket_fd);

}
/*to_monitor*/
void to_monitor_sendtowindows(char* data)
{

    in("monitoe 92\n");
    if((socket_fd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        in("monitoe 95\n");
        perror("socket error\n");
        exit(1);
    }
    in("monitoe 99\n");
    if(connect(socket_fd,(struct sockaddr *)&sockaddr_inServerAddress,sizeof(sockaddr_inServerAddress))!=0)
    {
        in("monitoe 102\n");
        printf("connect error !\n");
        close(socket_fd);
        exit(1);
    }
}
void to_back_sendtowindows(char* data)
{
    int i=80;
    char dis[20];
    char *skey;
    char in[16];
    char out[16];
    int j;
    for(i; i<=99; i++)
    {
        printf("%c",data[i]);
        if(data[i]!='#')
        {
            dis[i-80]=data[i];
        }
        else
        {
            break;
        }
    }
    dis[i-80]='\0';
    skey=IP_find_key(dis);
    printf("key:%s\n",skey);
    for(i=0;i<32;i++)
    {

        for(j=0;j<16;j++)
        {
            in[j]=data[i*16+j];
        }
        encrpt(in,skey,out);
        for(j=0;j<16;j++)
        {
            data[i*16+j]=out[j];
        }
    }
    printf("the distinatino ip is %s",dis);
    memset(&sockaddr_inServerAddress,0,sizeof(sockaddr_inServerAddress));

    sockaddr_inServerAddress.sin_family=AF_INET;
    sockaddr_inServerAddress.sin_addr.s_addr=inet_addr(dis);
    sockaddr_inServerAddress.sin_port=htons(8886);
    if((socket_fd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket error\n");
        exit(1);
    }
    if(connect(socket_fd,(struct sockaddr *)&sockaddr_inServerAddress,sizeof(sockaddr_inServerAddress))!=0)
    {
        printf("connect error !\n");
        close(socket_fd);
    }
    if(send(socket_fd,data,strlen(data),0)==-1)
    {
        printf("send error!\n");
    }
    close(socket_fd);

}

/*judge_type_byname.h*/
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
/**发送消息到指定的队列
*key为消息队列的关键字
*isContainType为常量，只能为0或1，0表示发送消息队列中不包括消息类型
*csh_common_functions.h
*/
int csh_sendMessageToQueue(key_t key,int isContainType,struct mymsg * msg)
{
    /*        printf("send one message\n");*/
    int qid;
    int result;
    int length;/*发送消息的长度*/
    if((qid=msgget(key,0666|IPC_CREAT))<0)
    {
        perror("msgget");
        exit(1);
    }
    /*根据isContainType的值来判断发送消息的长度*/
    if(isContainType==1) /*说明发送的消息要包括消息类型*/
    {
        length=sizeof( *msg);
    }
    else if(isContainType==0)
    {
        length=512;
    }
    else
    {
        printf("can shu lei xing errors");
        exit(1);
    }
    if((result=msgsnd(qid,msg,length,0))<0)
    {
        perror("msgsn");
        exit(1);
    }
    /*	printf("\nend of send msg\n");*/
    return result;
}

/*csh_common_functions.h*/
void  csh_readMessageFromQueue(key_t key,struct mymsg * msg,long msgtyp)
{
    /*       printf("\nbegin to read message\n");*/
    int qid;
    int result;
    if((qid=msgget(key,0666|IPC_CREAT))<0)
    {
        perror("msgget");
        exit(1);
    }
    msgrcv(qid,msg,sizeof(struct mymsg),msgtyp,0);
    /*	printf("\nend read message.\n");*/
}

/*
 * id_to_ip.h
 */
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

/*
 * select_types.h
 */
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

/*
 * primarymap.h
 */
 long primaryKeytoLong(char * dealid,char * type)
{
    /**从dealId的第八位开始截取子字符串
      交易次数最大取出来6位，交易类型最大为4位
    */
    char tempresult[11];
    int i,length;
    char tempdealid[6];
    long dealvalue,typevalue;
    int typelength;/*用来记录type的数值实际长度*/

    length=strlen(dealid);
    for(i=0; i<length; i++)
    {
        tempdealid[i]=dealid[8+i];
    }

    dealvalue=atol(tempdealid);
    printf("dealvalue is %ld\n",dealvalue);
    if(dealvalue>264521) /*只要交易的序列号大于这个数，我们让其从1开始循环，这样保证在一段时间内交易序列号的唯一性*/
    {
        dealvalue=dealvalue%264521+1;
    }
    /*解析交易类型,滤掉'type'这个字符串*/

    length=strlen(type);
    for(i=4; i<length&&i<8; i++) /*最大取4位，又由于存在'type'字符串*/
    {
        tempresult[i-4]=type[i];
    }
    tempresult[i-4]='\0';/*必须加结束符，否则会出错*/
    typevalue=atol(tempresult);
    typelength=strlen(tempresult);
    while(typelength>0) /*如果typevalue为123则dealvalue就要乘以1000*/
    {
        dealvalue*=10;
        typelength--;
    }
    dealvalue+=typevalue;
    return dealvalue;
}


/**发送消息到指定的队列
*key为消息队列的关键字
*isContainType为常量，只能为0或1，0表示发送消息队列中不包括消息类型
*/
int sendMessageToQueue(key_t key,int isContainType,struct mymsg * msg)
{
    printf("send one message\n");
    int qid;
    int result;
    int length;/*发送消息的长度*/
    if((qid=msgget(key,0666|IPC_CREAT))<0)
    {
        perror("msgget");
        exit(1);
    }

    /*根据isContainType的值来判断发送消息的长度*/
    if(isContainType==1)/*说明发送的消息要包括消息类型*/
    {
        length=sizeof( *msg);
    }
    else if(isContainType==0)
    {
        length=BUFSZ;
    }
    else
    {
        printf("can shu lei xing errors");
        exit(1);
    }
    printf("I am going to send message to win!\n");
    if((result=msgsnd(qid,msg,length,0))<0)
    {
        perror("msgsn");
        exit(1);
    }
    printf("\nend of send msg\n");
    return result;

}

/*从指定的消息队列中读取数据*/
int  readMessageFromQueue(key_t key,struct mymsg * msg,long msgtyp)
{
    int qid;
    int result;

    if((qid=msgget(key,0666|IPC_CREAT))<0)
    {
        perror("msgget");
        exit(1);
    }
    printf("I am going to read a message!\n");
    result=msgrcv(qid,msg,sizeof(struct mymsg),msgtyp,0);
    printf(" I had read a message already!\n");
    return result;
}


/*此函数根据子消息找出父交易号*/
void findfatherid(struct mymsg pmsg,char *result,int times)
{
    char sqltemp[200] = "select dealid from  deals where subdealid1='%s' and dealtype='%s'";
    char sqltemp1[200]="select dealid from  deals where subdealid2='%s' and dealtype='%s'";
    char parent[220];
    char send[220];
    char id[21],type[21],temp[21];
    int i,length;
    key_t key;
    struct mymsg tempmsg,sqltype;
    long typesql;
    /*解析出type和id*/
    for(i=0; i<20; i++)
    {
        if(pmsg.msg_buf[i]!='#')
        {
            id[i]=pmsg.msg_buf[i];
        }
        else
        {
            id[i]='\0';
        }
        if(pmsg.msg_buf[160+i]!='#')
        {
            type[i]=pmsg.msg_buf[160+i];
        }
        else
        {
            type[i]='\0';
        }
    }
    if(times==1)
        sprintf(parent,sqltemp,id,type);
    else if(times==2)
    {
        sprintf(parent,sqltemp1,id,type);
    }
    key=ftok(".",'w');
    readMessageFromQueue(key,&sqltype,0);
    typesql=atol(sqltype.msg_buf);
    printf("读取到的sql类型为：%s\n",sqltype.msg_buf);
    sprintf(send,"%010ld",typesql);

    sprintf(temp,"%010d",1);
    for(i=0; i<20; i++) /*字段个数*/
    {
        send[10+i]=temp[i];
    }
    sprintf(temp,"%010d",strlen(parent));/*消息正文的长度*/
    for(i=0; i<20; i++)
    {
        send[20+i]=temp[i];
    }
    length=strlen(parent);
    for(i=0; i<length; i++)
    {
        send[30+i]=parent[i];
    }
    send[30+i]='\0';
    printf("send is :%s\n",send);
    strcpy(tempmsg.msg_buf,send);
    tempmsg.msg_types=1;
    key=ftok(".",'n');
    sendMessageToQueue(key,0,&tempmsg);
    printf("查询父id的sql语句:%s\n",tempmsg.msg_buf);
    key=ftok(".",'p');
    while(readMessageFromQueue(key,&tempmsg,typesql)<0) /*取出消息类型为1的消息*/
    {
    }
    for(i=0; i<10; i++)
    {
        temp[i]=tempmsg.msg_buf[20+i];
    }
    length=atoi(temp);
    for(i=0; i<length; i++)
    {
        temp[i]=tempmsg.msg_buf[30+i];
    }
    temp[i]='\0';
    printf("查得附灰椎膇d号如下：%s\n",temp);
    strcpy(result,temp);
}


/*第一个参数为收到消息的内容,第二个参数为标识是要产生子交易2,还是直接发送到前端,1表示产生子交易2，0表示发送到前端,-1表示拆分*/
void chongzhen(struct mymsg pmsg,int *chaifen,int *times)
{
    char result[21];
    char temp[21];
    int start=0;/*记录收到消息的交易状态在condition_p对应的下标*/
    char *condition_p[]= {"1###################","0###################","-1##################"};
    /*解析sql语句用的变量*/
    char sqltemp[200] = "select dealid from  deals where subdealid1='%s' and dealtype='%s'";
    char parent[200];
    char send[220];
    char sendtemp[220];/*存放消息的长度和消息正文*/
    int i, length;
    /*解析出消息的主键*/
    char tempdealid[21], dealid[21];
    char temptype[21], type[21];
    struct mymsg tempmsg,sqltype;
    key_t key;
    long typesql;
    /*取出消息的交易状态*/
    for(i=140; i<160; i++)
    {
        temp[i-140]=pmsg.msg_buf[i];
    }
    temp[20]='\0';

    for(i=0; i<3; i++)
    {
        if(strcmp(temp,condition_p[i])==0)
        {
            start=i;
            break;
        }
    }

    /*在这儿先判断收到的消息是第一次拆分出来的结果，还是第二次的回复消息*/
    /*所以在这儿需要查询数据库*/
    /*根据解析出来的消息找匹配*/
    for (i = 0; i < 20; i++)
    {
        tempdealid[i] = pmsg.msg_buf[i];
    }
    for (i = 160; i < 180; i++)
    {
        temptype[i - 160] = pmsg.msg_buf[i];
    }

    for (i = 0; i < 20; i++)
    {
        if (tempdealid[i] != '#')
        {
            dealid[i] = tempdealid[i];
        }
        else
        {
            dealid[i]='\0';
        }
        if (temptype[i] != '#')
        {
            type[i] = temptype[i];
        }
        else
        {
            type[i]='\0';
        }
    }
    sprintf(parent, sqltemp,dealid,type);/*替换掉sql中参数*/

    /*把length转化为字符串存入send数组中*/
    sprintf(sendtemp,"%010d",strlen(parent));
    length=strlen(parent);

    /*填充消息的正文内容*/
    for (i = 10; i < length + 10; i++)
    {
        sendtemp[i] = parent[i - 10];
    }
    sendtemp[i]='\0';

    /*将前10个字节用发送的消息内容的消息类型来填充*/
    key=ftok(".",'w');
    readMessageFromQueue(key,&sqltype,0);
    typesql=atol(sqltype.msg_buf);
    printf("读取到的sql类型为：%s\n",sqltype.msg_buf);
    sprintf(send,"%010ld",typesql);
    sprintf(temptype,"%010d",1);/*字段的个数*/
    for(i=10; i<20; i++)
    {
        send[i]=temptype[i-10];
    }
    /*将sendtemp的内容加入到send数组的后面*/
    length=20+strlen(sendtemp);
    for(i=20; i<length; i++)
    {
        send[i]=sendtemp[i-20];
    }
    send[i]='\0';/*加结束符*/
    printf("*************send is :%s====>",send);
    strcpy(tempmsg.msg_buf,send);
    tempmsg.msg_types=1;
    tempmsg.msg_buf[strlen(tempmsg.msg_buf)]='\0';
    printf("此处向数据库发送第一次查询数据：%s\n",tempmsg.msg_buf);
    key=ftok(".",'n');
    sendMessageToQueue(key,0,&tempmsg);
    /*等待查询结果*/
    key=ftok(".",'p');
    printf("key=%x\n",key);

    while(readMessageFromQueue(key,&tempmsg,typesql)<0) /*取出消息类型为1的消息*/
    {
    }
    /*解析查询结果,查询结果为10个字节的消息类型，10个字节表示有多少条记录,再10字节表示每条记录的长度*/
    for(i=20; i<30; i++)
    {
        temp[i-20]=tempmsg.msg_buf[i];
    }
    temp[10]='\0';
    length=atoi(temp);
    printf("===========length=%d\n",length);
    for(i=30; i<30+length; i++)
    {
        temp[i-30]=tempmsg.msg_buf[i];
    }
    temp[i-30]='\0';
    /*将tempmsg消息的内容替换掉*/
    strcpy(tempmsg.msg_buf,temp);

    printf("收到数据库查询结果：%s\n",tempmsg.msg_buf);
    strcpy(result,temp);

    /*默认的是把这条消息当作子消息1来对待的,将查询出来的dealId放在了result中,查询不到结果的为0*/

    if(strcmp(result,"0")!=0) /*说明收到的消息是子消息1回复过来的*/
    {
        /*如果start==0说明是交易，否则不产生子交易2*/
        *times=1;
        if(start==0)
        {
            *chaifen=1;/*如果为1表示需要产生子交易2,并且此条消息不发送到前端*/
        }
        else
        {
            *chaifen=0;/*为零表示不需要产生子交易2,并且此条消息发送到前端*/
        }

    }
    else /*说明是子交易二返回的消息*/
    {
        *times=2;
        printf("++++start=%d\n++++",start);
        /*如果消息的状态为交易则直接发送到前台,否则就要冲正*/
        if(start==0)
        {
            *chaifen=0;
        }

        else
        {
            /*找出子交易1*/
            char sqltemp[200] = "select subdealid1,clientid,customerid  from deals where subdealid2='%s' and dealtype='%s'";
            char resulttemp[21];
            int resultnum;
            *chaifen=-1;/*-1表示冲正*/
            int start;
            struct mymsg sqltype;
            long typesql;
            int mm;
            /*以后换成数据库后，就不需要了*/
            /*	int typestart[6]={2,1,2,0,1,0};*/
            /*	int typeback[6]={1,2,0,2,0,1};*/
            struct pathtype pathtype1;
            char csh_select_type[21];
            /*char *address[]={"192.168.5.97########","192.168.5.86########","192.168.5.108#######"};*/
            char rout_p[21];/*="192.168.5.102#######";*/
            /*	char *type_p[]={"type7###############","type8###############","type9###############","type10##############","type11##############","type12##############"};
             */
            memset(rout_p,0,21);
            idToIp(0,rout_p);
            for(mm=19; mm>=strlen(rout_p); mm--)
            {
                rout_p[mm]='#';
            }
            /*	产生冲正消息*/
            /*第二次查询数据库，找出子交易1的详细相关信息*/
            sprintf(parent, sqltemp,dealid,type);/*替换掉sql中参数*/

            /*把length转化为字符串存入send数组中*/
            sprintf(sendtemp,"%010d",strlen(parent));
            length=strlen(parent);

            /*填充消息的正文内容*/
            for (i = 10; i < length + 10; i++)
            {
                sendtemp[i] = parent[i - 10];
            }

            /*将前10个字节用发送的消息内容的消息类型来填充*/
            key=ftok(".",'w');
            readMessageFromQueue(key,&sqltype,0);
            typesql=atol(sqltype.msg_buf);
            sprintf(send,"%010ld",typesql);
            sprintf(temptype,"%010d",3);/*字段的个数*/
            for(i=10; i<20; i++)
            {
                send[i]=temptype[i-10];
            }
            /*将sendtemp的内容加入到send数组的后面*/
            length=20+strlen(sendtemp);
            for(i=20; i<length; i++)
            {
                send[i]=sendtemp[i-20];
            }
            send[i]='\0';/*加结束符*/

            strcpy(tempmsg.msg_buf,send);
            tempmsg.msg_types=1;
            tempmsg.msg_buf[strlen(tempmsg.msg_buf)]='\0';
            printf("此处向数据库发送第二次查询数据：%s\n",tempmsg.msg_buf);
            key=ftok(".",'n');
            sendMessageToQueue(key,0,&tempmsg);
            /*等待查询结果*/
            memset(tempmsg.msg_buf,0,sizeof(tempmsg));
            key=ftok(".",'p');
            while(readMessageFromQueue(key,&tempmsg,typesql)<0) /*取出消息类型为1的消息*/
            {
            }
            printf("resut ========>from is :%s\n",tempmsg.msg_buf);

            /*解析查询结果,查询结果为10个字节的消息类型，10个字节表示有多少条记录,再10字节表示每条记录的长度*/

            /*解析第一个查询数据*/
            for(i=20; i<30; i++)
            {
                temp[i-20]=tempmsg.msg_buf[i];
            }
            temp[10]='\0';
            length=atoi(temp);
            for(i=0; i<length; i++)
            {
                temp[i]=tempmsg.msg_buf[i+30];
            }
            temp[i]='\0';
            printf("temp is:%s\n",temp);
            /*将tempmsg消息的内容替换掉*/
            strcpy(tempmsg.msg_buf,temp);
            start=30+strlen(temp);
            /*解析第二个数据*/
            for(i=0; i<10; i++)
            {
                temp[i]=tempmsg.msg_buf[start];
                start++;
            }
            temp[i]='\0';
            length=atoi(temp);
            for(i=0; i<length; i++)
            {
                temp[i]=tempmsg.msg_buf[start];
                start++;
            }
            temp[i]='\0';
            printf("temp1is:%s\n",temp);
            strcat(tempmsg.msg_buf,temp);
            /*解析第三个数据*/
            for(i=0; i<10; i++)
            {
                temp[i]=tempmsg.msg_buf[start];
                start++;
            }
            temp[i]='\0';
            length=atoi(temp);
            for(i=0; i<length; i++)
            {
                temp[i]=tempmsg.msg_buf[start];
                start++;
            }
            temp[i]='\0';
            printf("temp2 is:%s\n",temp);
            strcat(tempmsg.msg_buf,temp);

            /*读取冲正交易序列号*/
            memset(sqltype.msg_buf,0,sizeof(sqltype));
            key=ftok(".",'o');
            readMessageFromQueue(key,&sqltype,0);
            sqltype.msg_buf[strlen(sqltype.msg_buf)]='\0';
            printf("chong zhen is:%s\n",sqltype.msg_buf);
            /*连接最后结果*/
            strcat(sqltype.msg_buf,tempmsg.msg_buf);
            /*加上消息的源和目地*/

            for (i = 160; i < 180; i++)
            {
                temptype[i - 160] = pmsg.msg_buf[i];
            }
            temptype[20]='\0';
            memset(csh_select_type,0,21);
            strcpy(csh_select_type,temptype);
            for(mm=0; mm<20; mm++)
            {
                if(temptype[mm]!='#')
                {
                    csh_select_type[mm]=temptype[mm];
                }
                else
                {
                    break;
                }
            }
            select_type2_byname(csh_select_type,&pathtype1);
            /*
                        for(i=0;i<6;i++){
                        	if(strcmp(temptype,type_p[i])==0){
                        	 break;
                        	}
                        }
            printf("i is :%d\n",i);
            */
            /*把源加上*/
            memset(temp,0,21);
            strcpy(temp,pathtype1.destination_ip1);
            for(mm=19; mm>=strlen(temp); mm--)
            {
                temp[mm]='#';
            }
            strcat(sqltype.msg_buf,temp);
            /*把目地加上去*/
            /*strcpy(temp,address[typeback[i]]);*/
            strcat(sqltype.msg_buf,pathtype1.destination_ip2);

            printf("收到数据库第二次查询数据，并且写入了冲正队列:%s\n",sqltype.msg_buf);
            key=ftok(".",'q');
            sqltype.msg_types=1;
            sendMessageToQueue(key,0,&sqltype);
        }
    }
}


/*
 * sql.h
 */

/*此函数发送插入sql语句到父交易表*/
void sendinsertsql(struct mymsg pmsgs)
{
    char insertSql[300]="insert into deals values ('%s','%s','%s','%s','%s','%s','%s','%s','%s')";
    char parent[320];
    char send[320],sendtemp[320];
    char id[21],s[9][21],b[9][21],type[21],temp[21],temptype[21];
    int i,j,length;
    key_t key;
    struct mymsg tempmsg,sqlmsg,pmsg,sqltype;
    long typesql;
    /*从产生交易号的队列中取出子交易号*/
    printf("********************8%s\n",pmsgs.msg_buf);
    printf("I am going to get imformation!\n");
    memset(b,0,sizeof(b));
    for(i=0; i<9; i++)
    {
        for(j=0; j<20; j++)
        {
  //          printf("%c\n",pmsgs.msg_buf[i*20+j]);
            s[i][j]=pmsgs.msg_buf[i*20+j];
  //          printf("%c\n",s[i][j]);
            if(s[i][j]!='#')
            {
                b[i][j]=s[i][j];
   //              printf("%c\n",b[i][j]);
            }
            else
            {
                b[i][j]='\0';
//                printf("\n");
                break;
            }
        }
 //       puts(b[0]);
    }
 //   puts(b[0]);
    sprintf(parent,insertSql,b[0],b[1],b[2],b[3],b[4],b[5],b[6],b[7],b[8]);
    printf("The imformation:%s\n",parent);
    printf("shuzu de neirong wei :%s,%s,%s,%s,%s,%s,%s,%s,%s",b[0],b[1],b[2],b[3],b[4],b[5],b[6],b[7],b[8]);
    /*把length转化为字符串存入send数组中*/
    sprintf(sendtemp,"%010d",strlen(parent));
    length=strlen(parent);

    /*填充消息的正文内容*/
    for (i = 10; i < length + 10; i++)
    {
        sendtemp[i] = parent[i - 10];
    }
    sendtemp[i]='\0';
    printf("The message to dp!\n");
    /*将前10个字节用发送的消息内容的消息类型来填充*/
    key=ftok(".",'w');
    memset(sqltype.msg_buf,0,sizeof(sqltype.msg_buf));
    printf("read sqlid:\n");
    readMessageFromQueue(key,&sqltype,0);
    typesql=atol(sqltype.msg_buf);
    printf("sqlid:%ld\n",typesql);
    printf("读取到的sql类型为：%s\n",sqltype.msg_buf);
    sprintf(send,"%010ld",typesql);
    sprintf(temptype,"%010d",1);/*字段的个数*/
    for(i=10; i<20; i++)
    {
        send[i]=temptype[i-10];
    }
    /*将sendtemp的内容加入到send数组的后面*/
    length=20+strlen(sendtemp);
    for(i=20; i<length; i++)
    {
        send[i]=sendtemp[i-20];
    }
    send[i]='\0';/*加结束符*/
    printf("*************send is :%s====>",send);
    strcpy(tempmsg.msg_buf,send);
    tempmsg.msg_types=1;
    tempmsg.msg_buf[strlen(tempmsg.msg_buf)]='\0';
    key=ftok(".",'n');
    sendMessageToQueue(key,0,&tempmsg);
    printf("111111111111111111:发送到数据库的sql语句为：%s\n",tempmsg.msg_buf);
}

/*此函数发送插入sql语句到子交易表*/
void sendsubinsertsql(struct mymsg pmsgs)
{
    char insertSql[300]="insert into subdeals values ('%s','%s','%s','%s','%s','%s','%s','%s','%s')";
    char parent[320];
    char send[320],sendtemp[320];
    char id[21],s[8][21],b[8][21],type[21],temp[21],temptype[21];
    int i,j,length;
    key_t key;
    struct mymsg tempmsg,sqlmsg,pmsg,sqltype;
    long typesql;
    /*从产生交易号的队列中取出子交易号*/
    printf("********************8%s",pmsgs.msg_buf);
    for(i=0; i<9; i++)
    {
        for(j=0; j<20; j++)
        {
            s[i][j]=pmsgs.msg_buf[i*20+j];
            if(s[i][j]!='#')
            {
                b[i][j]=s[i][j];
            }
            else
            {
                b[i][j]='\0';
                break;
            }

        }
    }
    sprintf(parent,insertSql,b[0],b[1],b[2],b[3],b[4],b[5],b[6],b[7],b[8]);
    /*      printf("shuzu de neirong wei :%s,%s,%s,%s,%s,%s,%s,%s,%s",b[0],b[1],b[2],b[3],b[4],b[5],b[6],b[7],b[8]);*/
    /*把length转化为字符串存入send数组中*/
    sprintf(sendtemp,"%010d",strlen(parent));
    length=strlen(parent);

    /*填充消息的正文内容*/
    for (i = 10; i < length + 10; i++)
    {
        sendtemp[i] = parent[i - 10];
    }
    sendtemp[i]='\0';

    /*将前10个字节用发送的消息内容的消息类型来填充*/
    key=ftok(".",'w');
    readMessageFromQueue(key,&sqltype,0);
    typesql=atol(sqltype.msg_buf);
    /*      printf("读取到的sql类型为：%s\n",sqltype.msg_buf);*/
    sprintf(send,"%010ld",typesql);
    sprintf(temptype,"%010d",1);/*字段的个数*/
    for(i=10; i<20; i++)
    {
        send[i]=temptype[i-10];
    }
    /*将sendtemp的内容加入到send数组的后面*/
    length=20+strlen(sendtemp);
    for(i=20; i<length; i++)
    {
        send[i]=sendtemp[i-20];
    }
    send[i]='\0';/*加结束符*/
    /*      printf("*************send is :%s====>",send);		*/
    strcpy(tempmsg.msg_buf,send);
    tempmsg.msg_types=1;
    tempmsg.msg_buf[strlen(tempmsg.msg_buf)]='\0';
    key=ftok(".",'n');
    sendMessageToQueue(key,0,&tempmsg);
    /* printf("111111111111111111:发送到数据库的sql语句为：%s\n",tempmsg.msg_buf);*/
}

/*把消息转换成update语句发送到父交易表*/
void sendupdatesql(struct mymsg pmsg)
{
    char result[21];
    char temp[21];
    int start=0;/*记录收到消息的交易状态在condition_p对应的下标*/
    /*    char *type_p[]={"type1###############","type2###############","type3###############","type4###############","type5###############","type6###############"};*/
    /*	int typestart[6]={1,2,0,2,0,1};
    	char *address[]={"192.168.5.97########","192.168.5.86########","192.168.5.84########"};*/
    /*char rout_p[]="192.168.5.85########";*/
    /*解析sql语句用的变量*/
    char updateSql[300]="update deals set SourceId='%s', DestinationId='%s', DealStatus='%s' where DealId='%s'";
    char parent[300];
    char send[320];
    char sendtemp[320];/*存放消息的长度和消息正文*/
    int i, j,length;
    /*解析出消息的主键*/
    char tempdealid[21], dealid[21];
    char temptype[21], b[8][21],type[21],s[8][21];
    struct mymsg tempmsg,sqltype,sqlmsg;
    key_t key;
    long typesql;
    /*解读消息，读出相关的字段，以便形成update sql语句*/
    for(i=0; i<9; i++)
    {
        for(j=0; j<20; j++)
        {
            s[i][j]=pmsg.msg_buf[i*20+j];
            if(s[i][j]!='#')
            {
                b[i][j]=s[i][j];
            }
            else
            {
                b[i][j]='\0';
                break;
            }

        }
    }
    sprintf(parent,updateSql,b[3],b[4],b[7],b[0]);

    /*把length转化为字符串存入send数组中*/
    sprintf(sendtemp,"%010d",strlen(parent));
    length=strlen(parent);

    /*填充消息的正文内容*/
    for (i = 10; i < length + 10; i++)
    {
        sendtemp[i] = parent[i - 10];
    }
    sendtemp[i]='\0';

    /*将前10个字节用发送的消息内容的消息类型来填充*/
    key=ftok(".",'w');
    readMessageFromQueue(key,&sqltype,0);
    typesql=atol(sqltype.msg_buf);
    /*    printf("读取到的sql类型为：%s\n",sqltype.msg_buf);*/
    sprintf(send,"%010ld",typesql);
    sprintf(temptype,"%010d",1);/*字段的个数*/
    for(i=10; i<20; i++)
    {
        send[i]=temptype[i-10];
    }
    /*将sendtemp的内容加入到send数组的后面*/
    length=20+strlen(sendtemp);
    for(i=20; i<length; i++)
    {
        send[i]=sendtemp[i-20];
    }
    send[i]='\0';/*加结束符*/
    /*  printf("*************send is :%s====>",send);	*/
    strcpy(tempmsg.msg_buf,send);
    tempmsg.msg_types=1;
    tempmsg.msg_buf[strlen(tempmsg.msg_buf)]='\0';
    key=ftok(".",'n');
    sendMessageToQueue(key,0,&tempmsg);
    /*   printf("发送到数据库的sql语句为：%s\n",tempmsg.msg_buf);*/

}

/*把消息转换成update语句发送到子交易表*/
void sendsubupdatesql(struct mymsg pmsg)
{
    char result[21];
    char temp[21];
    int start=0;/*记录收到消息的交易状态在condition_p对应的下标*/
    /* char *type_p[]={"type1###############","type2###############","type3###############","type4###############","type5###############","type6###############"};
    int typestart[6]={1,2,0,2,0,1};
    char *address[]={"192.168.5.97########","192.168.5.86########","192.168.5.84########"};*/
    /*    char rout_p[]="192.168.5.85#########";*/
    /*解析sql语句用的变量*/
    char updateSql[300]="update subdeals set SourceId='%s', DestinationId='%s', DealStatus='%s' where DealId='%s'";
    char parent[300];
    char send[320];
    char sendtemp[320];/*存放消息的长度和消息正文*/
    int i, j,length;
    /*解析出消息的主键*/
    char tempdealid[21], dealid[21];
    char temptype[21], b[8][21],type[21],s[8][21];
    struct mymsg tempmsg,sqltype,sqlmsg;
    key_t key;
    long typesql;
    /*解读消息，读出相关的字段，以便形成update sql语句*/
    for(i=0; i<9; i++)
    {
        for(j=0; j<20; j++)
        {
            s[i][j]=pmsg.msg_buf[i*20+j];
            if(s[i][j]!='#')
            {
                b[i][j]=s[i][j];
            }
            else
            {
                b[i][j]='\0';
                break;
            }

        }
    }
    sprintf(parent,updateSql,b[3],b[4],b[7],b[0]);

    /*把length转化为字符串存入send数组中*/
    sprintf(sendtemp,"%010d",strlen(parent));
    length=strlen(parent);

    /*填充消息的正文内容*/
    for (i = 10; i < length + 10; i++)
    {
        sendtemp[i] = parent[i - 10];
    }
    sendtemp[i]='\0';

    /*将前10个字节用发送的消息内容的消息类型来填充*/
    key=ftok(".",'w');
    readMessageFromQueue(key,&sqltype,0);
    typesql=atol(sqltype.msg_buf);
    /*          printf("读取到的sql类型为：%s\n",sqltype.msg_buf);*/
    sprintf(send,"%010ld",typesql);
    sprintf(temptype,"%010d",1);/*字段的个数*/
    for(i=10; i<20; i++)
    {
        send[i]=temptype[i-10];
    }
    /*将sendtemp的内容加入到send数组的后面*/
    length=20+strlen(sendtemp);
    for(i=20; i<length; i++)
    {
        send[i]=sendtemp[i-20];
    }
    send[i]='\0';/*加结束符*/
    /*       printf("*************send is :%s====>",send);		*/
    strcpy(tempmsg.msg_buf,send);
    tempmsg.msg_types=1;
    tempmsg.msg_buf[strlen(tempmsg.msg_buf)]='\0';
    key=ftok(".",'n');
    sendMessageToQueue(key,0,&tempmsg);
    /*    printf("发送到数据库的sql语句为：%s\n",tempmsg.msg_buf);*/
}

/*更新父交易的交易状态*/
void sendsubupdatefathersql(struct mymsg pmsg)
{
    char result[21];
    char temp[21];
    int start=0;/*记录收到消息的交易状态在condition_p对应的下标*/
    /*    char *type_p[]={"type1###############","type2###############","type3###############","type4###############","type5###############","type6###############"};
    	int typestart[6]={1,2,0,2,0,1};
    	char *address[]={"192.168.5.97########","192.168.5.86########","192.168.5.84########"};*/
    /* char rout_p[]="192.168.5.85########";*/
    /*解析sql语句用的变量*/
    char updateSql[300]="update subdeals set SourceId='%s', DestinationId='%s', DealStatus='%s' where DealId='%s'";
    char parent[300];
    char send[320];
    char sendtemp[320];/*存放消息的长度和消息正文*/
    int i, j,length;
    /*解析出消息的主键*/
    char tempdealid[21], dealid[21];
    char temptype[21], b[8][21],type[21],s[8][21],id[14];
    struct mymsg tempmsg,sqltype,sqlmsg;
    key_t key;
    long typesql;
    /*解读消息，读出相关的字段，以便形成update sql语句*/
    for(i=0; i<9; i++)
    {
        for(j=0; j<20; j++)
        {
            s[i][j]=pmsg.msg_buf[i*20+j];
            if(s[i][j]!='#')
            {
                b[i][j]=s[i][j];
            }
            else
            {
                b[i][j]='\0';
                break;
            }

        }
    }
    findfatherid(pmsg,id,2);
    sprintf(parent,updateSql,b[3],b[4],b[7],id);

    /*把length转化为字符串存入send数组中*/
    sprintf(sendtemp,"%010d",strlen(parent));
    length=strlen(parent);

    /*填充消息的正文内容*/
    for (i = 10; i < length + 10; i++)
    {
        sendtemp[i] = parent[i - 10];
    }
    sendtemp[i]='\0';

    /*将前10个字节用发送的消息内容的消息类型来填充*/
    key=ftok(".",'w');
    readMessageFromQueue(key,&sqltype,0);
    typesql=atol(sqltype.msg_buf);
    /*   printf("读取到的sql类型为：%s\n",sqltype.msg_buf);*/
    sprintf(send,"%010ld",typesql);
    sprintf(temptype,"%010d",1);/*字段的个数*/
    for(i=10; i<20; i++)
    {
        send[i]=temptype[i-10];
    }
    /*将sendtemp的内容加入到send数组的后面*/
    length=20+strlen(sendtemp);
    for(i=20; i<length; i++)
    {
        send[i]=sendtemp[i-20];
    }
    send[i]='\0';/*加结束符*/
    /*    printf("*************send is :%s====>",send);		*/
    strcpy(tempmsg.msg_buf,send);
    tempmsg.msg_types=1;
    tempmsg.msg_buf[strlen(tempmsg.msg_buf)]='\0';
    key=ftok(".",'n');
    sendMessageToQueue(key,0,&tempmsg);
    /*  printf("发送到数据库的sql语句为：%s\n",tempmsg.msg_buf);*/
}

/*
 * mysql.h
 */
MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
char *database = "localdb";
char sql[100];
char findkey[20];

//检查IP是否在trust表里面存在，存在则返回1不存在返回0
int checkIP(char IP[]) {
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
			0)) {
		printf("%s\n", mysql_error(conn));
		perror("mysql_real_connect error!");
		exit(1);
	}
	sprintf(sql, "select count(*) from trust where IP='%s'", IP);
	if (mysql_query(conn, sql)) {
		printf("%s\n", mysql_error(conn));
		perror("mysql_query_error!");
		exit(1);
	}
	res = mysql_use_result(conn);
	while ((row = mysql_fetch_row(res)) != NULL) {
		printf("%s\n", row[0]);
		mysql_free_result(res);
		mysql_close(conn);
		return 1;
	}
	mysql_free_result(res);
	mysql_close(conn);
	return 0;

}

//插入IP和key进入trustKey表，成功返回1，失败返回0
int key_ip_in(char key[], char IP[]) {
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
			0)) {
		printf("%s\n", mysql_error(conn));
		perror("mysql_real_connect error!");
		mysql_close(conn);
		return 0;
		//  exit(1);
	}
	sprintf(sql, "insert into TrustKey values('%s','%s')", IP, key);
	if (!(res = (mysql_query(conn, sql)))) {
		printf("inserted %lu rows\n",
				(unsigned long) mysql_affected_rows(conn));
		mysql_free_result(res);
		mysql_close(conn);
		return 1;
	} else {
		printf("%s\n", mysql_error(conn));
		perror("mysql_query_error!");
	}

	mysql_close(conn);
	return 0;

}

//把IP和key插入受信任的trust表里面
int IP_KEY_in(char IP[], char key[]) {
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
			0)) {
		printf("%s\n", mysql_error(conn));
		perror("mysql_real_connect error!");
		exit(1);
	}
	sprintf(sql, "insert into trust values('%s','%s')", IP, key);
	if (!(res = (mysql_query(conn, sql)))) {
		printf("inserted %lu rows\n",
				(unsigned long) mysql_affected_rows(conn));
		mysql_free_result(res);
		mysql_close(conn);
		return 1;
	} else {
		printf("%s\n", mysql_error(conn));
		perror("mysql_query_error!");
		//  exit(1);
	}
	//  mysql_free_result(res);
	mysql_close(conn);
	return 0;

}

//通过IP查找key，成功则返回key指针，失败返回NULL
char *IP_find_key(char IP[]) {
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
			0)) {
		printf("%s\n", mysql_error(conn));
		perror("mysql_real_connect error!");
		exit(1);
	}
	sprintf(sql, "select skey from TrustKey where IP='%s'", IP);
	//   printf("OK115!\n");
	if (mysql_query(conn, sql)) {
		printf("%s\n", mysql_error(conn));
		perror("mysql_query_error!");
		exit(1);
	}
	res = mysql_use_result(conn);
	//   printf("OK122!\n");
	while ((row = mysql_fetch_row(res)) != NULL) {
		//       printf("OK124!\n");
		strcpy(findkey, row[0]);
		mysql_free_result(res);
		mysql_close(conn);
		printf("%s\n", findkey);
		return (char *) &findkey;
	}
	//   printf("OK125!\n");
	mysql_free_result(res);
	mysql_close(conn);
	perror("db error!");
	//   exit(1);
	return NULL;

}

//通过IP查找初始key，成功则返回key指针，失败返回NULL
char *IP_find_key_again(char IP[]) {
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
			0)) {
		printf("%s\n", mysql_error(conn));
		perror("mysql_real_connect error!");
		exit(1);
	}
	sprintf(sql, "select SKEY from trust where IP='%s'", IP);
	//   printf("OK115!\n");
	if (mysql_query(conn, sql)) {
		printf("%s\n", mysql_error(conn));
		perror("mysql_query_error!");
		exit(1);
	}
	res = mysql_use_result(conn);
	//   printf("OK122!\n");
	while ((row = mysql_fetch_row(res)) != NULL) {
		//       printf("OK124!\n");
		strcpy(findkey, row[0]);
		mysql_free_result(res);
		mysql_close(conn);
		//     printf("%s\n",findkey);
		return (char *) &findkey;
	}
	//   printf("OK125!\n");
	mysql_free_result(res);
	mysql_close(conn);
	perror("db error!");
	// exit(1);
	return NULL;

}

//清空表TrustKey,成功返回1，失败返回0
int clean_TrustKey() {
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
			0)) {
		printf("%s\n", mysql_error(conn));
		perror("mysql_real_connect error!");
		exit(1);
	}
	sprintf(sql, "delete from TrustKey");
	if (!(res = (mysql_query(conn, sql)))) {
		printf("delete %lu rows\n", (unsigned long) mysql_affected_rows(conn));
		mysql_free_result(res);
		mysql_close(conn);
		return 1;
	} else {
		printf("%s\n", mysql_error(conn));
		perror("mysql_query_error!");
		exit(1);
	}
	mysql_free_result(res);
	mysql_close(conn);
	return 0;

}

//通过IP删除一行数据
int del_IP_KEY(char IP[]) {
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
			0)) {
		printf("%s\n", mysql_error(conn));
		perror("mysql_real_connect error!");
		exit(1);
	}
	sprintf(sql, "delete from trust where IP='%s';", IP);
	if (!(res = (mysql_query(conn, sql)))) {
		printf("delete %lu rows\n", (unsigned long) mysql_affected_rows(conn));
		mysql_free_result(res);
		mysql_close(conn);
		return 1;
	} else {
		printf("%s\n", mysql_error(conn));
		perror("mysql_query_error!");
		exit(1);
	}
	mysql_free_result(res);
	mysql_close(conn);
	return 0;

}

//通过IP修改一行数据
int alter_IP_KEY(char IP[], char key[]) {
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
			0)) {
		printf("%s\n", mysql_error(conn));
		perror("mysql_real_connect error!");
		exit(1);
	}
	sprintf(sql, "update trust set SKEY='%s' where IP='%s'", key, IP);
	if (!(res = (mysql_query(conn, sql)))) {
		printf("update %lu rows\n", (unsigned long) mysql_affected_rows(conn));
		mysql_free_result(res);
		mysql_close(conn);
		return 1;
	} else {
		printf("%s\n", mysql_error(conn));
		perror("mysql_query_error!");
		exit(1);
	}
	mysql_free_result(res);
	mysql_close(conn);
	return 0;
}

