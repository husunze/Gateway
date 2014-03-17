/*
 * csh_common_functions.h
 *
 *  Created on: 2013年8月13日
 *      Author: oracle
 */

#ifndef CSH_COMMON_FUNCTIONS_H_
#define CSH_COMMON_FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "config.h"


/**发送消息到指定的队列
*key为消息队列的关键字
*isContainType为常量，只能为0或1，0表示发送消息队列中不包括消息类型
*/
int csh_sendMessageToQueue(key_t key,int isContainType,struct mymsg * msg);

void  csh_readMessageFromQueue(key_t key,struct mymsg * msg,long msgtyp);


#endif /* CSH_COMMON_FUNCTIONS_H_ */
