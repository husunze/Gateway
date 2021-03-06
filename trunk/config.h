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
//#define TO_IDMAX  512/*to_id*/
#define BUFSZ 512
#define MAXDATASIZE 20/*judge1.h*/
#define PORTF 8881/*rcv_font.h*/
#define PORTB 8884/*rcv_back.h*/


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

/*judge1*/
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


#endif /* CONFIG_H_ */
