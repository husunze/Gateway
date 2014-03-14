#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "rcv_reg.h"
#include "deal_reg_msg.h"
#include "error.h"
#include "auto_reg.h"

int main()
{
    char *logname = "main.txt";
    pthread_t rcv_reg_id;
    int rcv_reg_ret;
    pthread_t deal_reg_msg_id;
    int deal_reg_msg_ret;
    pthread_t auto_reg_id;
    int auto_reg_ret;
    pthre
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
    pthread_join(rcv_reg_id, NULL);
    pthread_join(deal_reg_msg_id, NULL);
    pthread_join(auto_reg_id, NULL);
    return 0;
}
