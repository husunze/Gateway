/*
 * sql.h
 *
 *  Created on: 2013年8月13日
 *      Author: oracle
 */

#ifndef SQL_H_
#define SQL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define BUFSZ 512
#define MAXDATASIZE 21


#include"primaryMap.h"


/*此函数发送插入sql语句到父交易表*/
void sendinsertsql(struct mymsg pmsgs);


/*此函数发送插入sql语句到子交易表*/

void sendsubinsertsql(struct mymsg pmsgs);

/*把消息转换成update语句发送到父交易表*/
void sendupdatesql(struct mymsg pmsg);



/*把消息转换成update语句发送到子交易表*/
void sendsubupdatesql(struct mymsg pmsg);

/*更新父交易的交易状态*/
void sendsubupdatefathersql(struct mymsg pmsg);



#endif /* SQL_H_ */
