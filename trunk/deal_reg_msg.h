#ifndef DEAL_REG_MSG_H_INCLUDED
#define DEAL_REG_MSG_H_INCLUDED

void deal_reg_msg_run(){
    int qid,qid2;
    key_t msgkey,msgkey2;
    int msglen;
    char IP[20];
    char key[20];
    int i;
    int sign;
    struct mymsg temp;
    char *logname = "deal_reg_msg.txt";
    //设置消息队列
    if((msgkey=ftok(".",'K'))<0)
    {
        char *message = "ftok error.\n";
        log(logname, strlen(logname), message, sizeof(message));
        exit(1);
    }

    if((qid=msgget(msgkey,IPC_CREAT|0666))<0)
    {
        char *message = "msgget error.\n";
        log(logname, strlen(logname), message, sizeof(message));
        exit(1);
    }
    if((msgkey2=ftok(".",'k'))<0)
    {
        char *message = "ftok error.\n";
        log(logname, strlen(logname), message, sizeof(message));
        exit(1);
    }
    if((qid2=msgget(msgkey2,IPC_CREAT|0666))<0)
    {
        char *message = "msgget error.\n";
        log(logname, strlen(logname), message, sizeof(message));
        exit(1);
    }
    printf("qid :%d\n",qid);
    printf("qid of auto_reg:%d\n",qid2);
    msglen=sizeof(struct mymsg)-4;
    //开始接受消息
    while((msgrcv(qid,&temp,512,0,0))!=-1)
    {
        //这个地方写所有的处理消息
        printf("%s\n",temp.msg_buf);
        log(logname, strlen(logname), temp.msg_buf, sizeof(temp.msg_buf));
        for(i=0;i<20;i++)
        {
            IP[i]=temp.msg_buf[i];
            if(IP[i]=='#')
            {
                IP[i]='\0';
                break;
            }
        }
        log(logname, strlen(logname), IP, sizeof(IP));
        printf("IP:%s\n",IP);
        for(i=40;i<60;i++)
        {
            key[i-40]=temp.msg_buf[i];
            if(key[i-40]=='#')
            {
                key[i-40]='\0';
                break;
            }
        }
        printf("key:%s\n",key);
        log(logname, strlen(logname), key, sizeof(key));
        if(key_ip_in(key,IP))
        {
           char *message = "key and ip insert into db!";
           log(logname, strlen(logname), message, sizeof(message));
           printf("key and ip insert into db!\n");
        }
        else
        {
            char *message = "key and ip insert wrong!";
            log(logname, strlen(logname), message, sizeof(message));
            printf("key and ip insert wrong!\n");
        }
        //这个地方我们要把消息放如消息对列‘k’,等待进一步的处理

        printf("qid of auto_reg:%d\n",qid2);
        temp.msg_types=1;
   //     msglen=sizeof(struct mymsg)-4;
       // count=msgsnd(qid,&msg1,sizeof(msg1.msg_buf),0);
        if(msgsnd(qid2,&temp,sizeof(temp.msg_buf),0)<0)
        {
          //  printf("mssage send error,count=%d!",count);
            char *message = "msgsnd error!";
            log(logname, strlen(logname), message, sizeof(message));
            exit(1);
        }
        printf("msgsend OK!\n");
//       }
//       else
//       {
//           printf("IP is a untrusted IP!\n");
//       }
    }
    perror("msgrcv error!");
    printf("msgrcv error!\n");
    exit(1);
}

#endif // DEAL_REG_MSG_H_INCLUDED
