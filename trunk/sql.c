/*
 * sql.c
 *
 *  Created on: 2013年8月13日
 *      Author: oracle
 */

#include "sql.h"


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



