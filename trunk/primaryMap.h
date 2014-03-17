/*
 * primaryMap.h
 *
 *  Created on: 2013年8月13日
 *      Author: oracle
 */

#ifndef PRIMARYMAP_H_
#define PRIMARYMAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "config.h"
#include "select_types.h"


#define BUFSZ 512
#define MAXDATASIZE 21

long primaryKeytoLong(char * dealid,char * type);


/**发送消息到指定的队列
*key为消息队列的关键字
*isContainType为常量，只能为0或1，0表示发送消息队列中不包括消息类型
*/
int sendMessageToQueue(key_t key,int isContainType,struct mymsg * msg);

/*从指定的消息队列中读取数据*/
int  readMessageFromQueue(key_t key,struct mymsg * msg,long msgtyp);


/*此函数根据子消息找出父交易号*/
void findfatherid(struct mymsg pmsg,char *result,int times);


/*第一个参数为收到消息的内容,第二个参数为标识是要产生子交易2,还是直接发送到前端,1表示产生子交易2，0表示发送到前端,-1表示拆分*/
void chongzhen(struct mymsg pmsg,int *chaifen,int *times);


#endif /* PRIMARYMAP_H_ */
