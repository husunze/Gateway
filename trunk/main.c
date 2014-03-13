#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "rcv_reg.h"
#include "error.h"

int main()
{
    char *logname = "main.txt";
    pthread_t rcv_reg_id;
    int rcv_reg_ret;
    rcv_reg_ret = pthread_create(&rcv_reg_id, NULL, (void *)rcv_reg_run, NULL);
    if(rcv_reg_ret != 0){
        char *message = "Create thread error.";
        log(logname, strlen(logname), message, strlen(message));
        exit(-1);
    }
    pthread_join(rcv_reg_id, NULL);
    return 0;
}
