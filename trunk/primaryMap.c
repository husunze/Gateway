/*
 * primaryMap.c
 *
 *  Created on: 2013年8月13日
 *      Author: oracle
 */

#include "primaryMap.h"

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


