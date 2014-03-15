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

#define server "localhost"
#define user "root"
#define password "hsz67235690"

#define DATABASEPORT 1234

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
};/*judge1*/



#endif /* CONFIG_H_ */
