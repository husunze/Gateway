/*
 * config.h
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define MAX 20
#define MIN 10
#define BUF 512
#define LEN 10
#define MAXDATASIZE 20
#define RCV_REG_PORT 9999
#define RCV_SQL_RES_PORT 7777
#define DATABASEIP "172.16.15.18"
#define DATABASEPORT 1234

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "hsz67235690"



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <mysql/mysql.h>
#include <netinet/in.h>
#define BUFSZ 512
#define MAXDATASIZE 21

struct mymsg
{
    long msg_types;
    char msg_buf[BUF];
};
/*消息队列结构体 */


struct IdIpMsg/*id和ip对应信息表结构*/
{
    int id; /*机器编号*/
    char ip[MAX];/*机器编号对应的ip*/
};

struct TypeMsg1
{
    int sourceID;
    int destinationID;
    int type;
};

struct TypeMsg2
{
    int sourceID;
    int destinationID1;
    int destinationID2;
    int type;
};

/*judge1.h*/
struct message
{
    char deal_id[MAXDATASIZE];
    char client_id[MAXDATASIZE];
    char client_addr[MAXDATASIZE];
    char source_addr[MAXDATASIZE];
    char desitination_addr[MAXDATASIZE];
    char child1_id[MAXDATASIZE];
    char chlid2_id[MAXDATASIZE];
    char condition[MAXDATASIZE];
    char type[MAXDATASIZE];
};

/*judge_type_byname.h*/
void judge_type_byname(char type_name[],char result[]);

int socket_fd;
struct sockaddr_in sockaddr_inServerAddress;
/*to_font.h*/
void sendtowindows(char* data);
/*to_id.h*/
void sendtowindowsto_id(char* data);
/*to_monitor.h*/
void to_monitor_sendtowindows(char* data);
/*to_back*/
void to_back_sendtowindows(char* data);

/*csh_type_def.h*/
struct pathtype{
        char type_name[21];
        char source_ip[21];
        char destination_ip1[21];
        char destination_ip2[21];
};


/**发送消息到指定的队列
*key为消息队列的关键字
*isContainType为常量，只能为0或1，0表示发送消息队列中不包括消息类型
*csh_common_functions.h
*/
int csh_sendMessageToQueue(key_t key,int isContainType,struct mymsg * msg);
void  csh_readMessageFromQueue(key_t key,struct mymsg * msg,long msgtyp);

/*
 * id_to_ip.h
 */
char *idToIp(int id,char ip_result[]);

/*
 * select_types.h
 */
void select_type2_byname(char type_name[],struct pathtype* yourtype);
void select_type1_byname(char type_name[],struct pathtype* yourtype);

/*
 * primarymap.h
 */
long primaryKeytoLong(char * dealid,char * type);
/**发送消息到指定的队列
*key为消息队列的关键字
*isContainType为常量，只能为0或1，0表示发送消息队列中不包括消息类型
*/
int sendMessageToQueue(key_t key,int isContainType,struct mymsg * msg);
/*从指定的消息队列中读取数据*/
int readMessageFromQueue(key_t key,struct mymsg * msg,long msgtyp);
/*此函数根据子消息找出父交易号*/
void findfatherid(struct mymsg pmsg,char *result,int times);
/*第一个参数为收到消息的内容,第二个参数为标识是要产生子交易2,还是直接发送到前端,1表示产生子交易2，0表示发送到前端,-1表示拆分*/
void chongzhen(struct mymsg pmsg,int *chaifen,int *times);


/*
 * sql.h
 */
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

/*
 * mysql_use.h
 */
#define server "localhost"
#define user "root"
#define password "hsz67235690"

/*
 * mysql.h
 */
//检查IP是否在trust表里面存在，存在则返回1不存在返回0
int checkIP(char IP[]);
//插入IP和key进入trustKey表，成功返回1，失败返回0
int key_ip_in(char key[], char IP[]);
//把IP和key插入受信任的trust表里面
int IP_KEY_in(char IP[], char key[]);
//通过IP查找key，成功则返回key指针，失败返回NULL
char *IP_find_key(char IP[]);
//通过IP查找初始key，成功则返回key指针，失败返回NULL
char *IP_find_key_again(char IP[]);
//清空表TrustKey,成功返回1，失败返回0
int clean_TrustKey();
//通过IP删除一行数据
int del_IP_KEY(char IP[]);
//通过IP修改一行数据
int alter_IP_KEY(char IP[], char key[]);

#endif /* CONFIG_H_ */
