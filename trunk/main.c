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
#include "judge1.h"
#include "judge2.h"
#include "to_id.h"
#include "rcv_font.h"
#include "rcvfont.h"
#include "to_monitor.h"
#include "to_back.h"
#include "rcv_back.h"
#include "rcvback.h"
#include "to_font.h"

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
    pthread_t judge1_id;
    int judge1_ret;
    pthread_t judge2_id;
    int judge2_ret;
    pthread_t to_id_id;
    int to_id_ret;
    pthread_t rcv_font_id;
    int rcv_font_ret;
    pthread_t rcvfont_id;
    int rcvfont_ret;
    pthread_t to_monitor_id;
    int to_monitor_ret;
    pthread_t to_back_id;
    int to_back_ret;
    pthread_t rcv_back_id;
    int rcv_back_ret;
    pthread_t rcvback_id;
    int rcvback_ret;
    pthread_t to_font_id;
    int to_font_ret;



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
    judge1_ret = pthread_create(&judge1_id, NULL, (void *)judge1_run, NULL);
    if(judge1_ret != 0){
        char *message = "Create judge1 thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    judge2_ret = pthread_create(&judge2_id, NULL, (void *)judge2_run, NULL);
    if(judge2_ret != 0){
        char *message = "Create judge2 thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    to_id_ret = pthread_create(&to_id_id, NULL, (void *)to_id_run, NULL);
    if(to_id_ret != 0){
        char *message = "Create to_id thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    rcv_font_ret = pthread_create(&rcv_font_id, NULL, (void *)rcv_font_run, NULL);
    if(rcv_font_ret != 0){
        char *message = "Create rcv_font thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    rcvfont_ret = pthread_create(&rcvfont_id, NULL, (void *)rcvfont_run, NULL);
    if(rcvfont_ret != 0){
        char *message = "Create rcvfont thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    to_monitor_ret = pthread_create(&to_monitor_id, NULL, (void *)to_monitor_run, NULL);
    if(to_monitor_ret != 0){
        char *message = "Create to_monitor thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    to_back_ret = pthread_create(&to_back_id, NULL, (void *)to_back_run, NULL);
    if(to_back_ret != 0){
        char *message = "Create to_back thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
      rcv_back_ret = pthread_create(&rcv_back_id, NULL, (void *)rcv_back_run, NULL);
    if(rcv_back_ret != 0){
        char *message = "Create rcv_back thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    rcvback_ret = pthread_create(&rcvback_id, NULL, (void *)rcvback_run, NULL);
    if(rcvback_ret != 0){
        char *message = "Create rcvback thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    to_font_ret = pthread_create(&to_font_id, NULL, (void *)to_font_run, NULL);
    if(to_font_ret != 0){
        char *message = "Create to_font thread error.";
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
    pthread_join(judge1_id, NULL);
    pthread_join(judge2_id, NULL);
    pthread_join(to_id_id, NULL);
    pthread_join(rcv_font_id, NULL);
    pthread_join(rcvfont_id, NULL);
    pthread_join(to_monitor_id, NULL);
    pthread_join(to_back_id, NULL);
    pthread_join(rcv_back_id, NULL);
    pthread_join(rcvback_id, NULL);
    pthread_join(to_font_id,NULL);

    return 0;
}
