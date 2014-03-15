#ifndef TO_TYPE_H_INCLUDED
#define TO_TYPE_H_INCLUDED

void to_type_run(){
    int qid;
    key_t key;
    int len;
    struct mymsg pmsg;
    /*
     	if(argc!=2)
    {
    	printf("Usage:\n");
    	printf("To_back<protnum>\n");
    	exit(1);
    }

    */
    key=ftok(".",'l');
    printf("key=%x\n",key);
    if((qid=msgget(key,IPC_CREAT|0666))==-1)
    {
        perror("msgget error!");
        exit(1);
    }
    printf("qid=%d\n",qid);

    for(;;)
    {
        len=msgrcv(qid,&pmsg,sizeof(pmsg.msg_buf),0,0);
        if(len<0)
        {
            perror("msgrcv error!");
            exit(1);
        }
        else if(len==0)
        {
            printf("no date in quene!");
            exit(1);
        }

        else
        {
            printf("i will send a message to windows ,the message is %s\n",pmsg.msg_buf);
            printf("_________________________________\n");
        }
        to_type_sendtowindows(pmsg.msg_buf);
    }/*end while*/
    return 0;
}

void to_type_sendtowindows(char* data)
{
    int i=0;
    int j;
    char *k;
    char in[16];
    char out[16];
    char dis[20];
    int socket_fd;
    struct sockaddr_in sockaddr_inServerAddress;
    for(i; i<20; i++)
    {
        printf("%c",data[i]);
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
    printf("the distinatino ip is %s\n",dis);
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
    sockaddr_inServerAddress.sin_port=htons(9991);
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
        printf("send error!\n");
    else
        printf("Send successfully!\n");
    close(socket_fd);

}

#endif // TO_TYPE_H_INCLUDED
