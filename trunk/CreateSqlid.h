#ifndef CREATESQLID_H_INCLUDED
#define CREATESQLID_H_INCLUDED

void createsqlid_run(){

    struct mymsg
    {
        long msgtype;
        char buff[11];
    };

    struct mymsg mmsg;
    struct mymsg msg2;
    key_t mykey;
    int i;
    int qid;
    long did=1;
    char id[21];
    mykey = ftok(".",'w');
    qid = msgget(mykey,IPC_CREAT|0666);
    if(qid<0)
    {
        printf("msgget error");
    }
    printf("-----qid=%d------\n",qid);
    while(1)
    {
        time_t timp;
        struct tm *p;
        time(&timp);
        p = gmtime(&timp);
        sprintf(id,"%010ld",did);
        did++;
        for(i=0; i<10; i++)
        {
            mmsg.buff[i]=id[i];
        }
        mmsg.buff[10]='\0';
        mmsg.msgtype=1;
        if(msgsnd(qid,&mmsg,strlen(mmsg.buff),0)<0)
        {
            printf("send msg error\n");
        }
      //  printf("sqlid=>%s\n",mmsg.buff);
        sleep(1);
    }
}


#endif // CREATESQLID_H_INCLUDED
