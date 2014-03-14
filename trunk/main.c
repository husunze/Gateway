#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "rcv_reg.h"
#include "deal_reg_msg.h"
#include "error.h"
#include "auto_reg.h"
#include "CreateSqlid.h"
#include "snd_sql.h"
#include "rcv_sqlRes.h"
#include "to_type.h"

int main()
{
    char *logname = "main.txt";
    pthread_t rcv_reg_id;
    int rcv_reg_ret;
    pthread_t deal_reg_msg_id;
    int deal_reg_msg_ret;
    pthread_t auto_reg_id;
    int auto_reg_ret;
    pthread_t createsqlid_id;
    int createsqlid_ret;
    pthread_t snd_sql_id;
    int snd_sql_ret;
    pthread_t rcv_sqlRes_id;
    int rcv_sqlRes_ret;
    pthread_t to_type_id;
    int to_type_ret;
    rcv_reg_ret = pthread_create(&rcv_reg_id, NULL, (void *)rcv_reg_run, NULL);
    if(rcv_reg_ret != 0){
        char *message = "Create rcv_reg thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    deal_reg_msg_ret = pthread_create(&deal_reg_msg_id, NULL, (void *)deal_reg_msg_run, NULL);
    if(deal_reg_msg_ret != 0){
        char *message = "Create deal_reg_msg thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    auto_reg_ret = pthread_create(&auto_reg_id, NULL, (void *)auto_reg_run, NULL);
    if(auto_reg_ret != 0){
        char *message = "Create auto_reg thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    createsqlid_ret = pthread_create(&createsqlid_id, NULL, (void *)createsqlid_run, NULL);
    if(createsqlid_ret != 0){
        char *message = "Create createsqlid thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    snd_sql_ret = pthread_create(&snd_sql_id, NULL, (void *)snd_sql_run, NULL);
    if(snd_sql_ret != 0){
        char *message = "Create snd_sql thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    rcv_sqlRes_ret = pthread_create(&rcv_sqlRes_id, NULL, (void *)rcv_sqlRes_run, NULL);
    if(rcv_sqlRes_ret != 0){
        char *message = "Create rcv_sqlRes thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    to_type_ret = pthread_create(&to_type_id, NULL, (void *)to_type_run, NULL);
    if(rcv_sqlRes_ret != 0){
        char *message = "Create to_type thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    pthread_join(rcv_reg_id, NULL);
    pthread_join(deal_reg_msg_id, NULL);
    pthread_join(auto_reg_id, NULL);
    pthread_join(createsqlid_id, NULL);
    pthread_join(snd_sql_id, NULL);
    pthread_join(rcv_sqlRes_id, NULL);
    pthread_join(to_type_id, NULL);
    return 0;
}
