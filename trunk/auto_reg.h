#ifndef AUTO_REG_H_INCLUDED
#define AUTO_REG_H_INCLUDED
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>
#include <stdio.h>
#include"getconn.h"
#include"rcvfrommsgq.h"
#include"rcvfromterm.h"
#include"sendtype.h"
#include"sendtodb.h"
#include"sendtoterm.h"
#include"gettype.h"
#include"error.h"

void auto_reg_run(){
    key_t fromdbKey, todbKey, fromtermKey, totermKey, sqlidKey, idkey;
    int *idNum; /*各机器编号指针*/
    int *idNum1;
    int num; /*记录机器总数*/
    int i, j, k, m; /*循环控制变量*/
    int typeNum = 0; /*记录type值已经分配到何处*/
    int typeNum1;/*type1表中的type最大值*/
    int typeNum2;/*type2表中的type最大值*/
    char *ipMsg; /*指向记录刚请求连接的机器ip信息的字符指针*/
    char trueIp[20];
    char *status;/*机器的连接字段*/
    char sql[200]; /*将向数据库发送含sql语句的字符串*/
    struct IdIpMsg temp; /*用来记录刚请求连接的机器的id和ip信息*/
    struct IdIpMsg tempsr; /*用来与前后端通信的机器id和ip信息*/
    struct TypeMsg1 *msg1; /*一对一type指针*/
    struct TypeMsg2 *msg2; /*一对二type指针*/
    char truesql[200]; /*实际sql语句*/
    char sqlRes[512]; /*数据库返回的结果串*/
    char id[10]; /*数据库中查询的ip对应的id*/
    char id1[10];
    char ip[20]; /*临时存储查询到的机器的ip*/
    char lenth[11]; /*数据库返回结果中的长度字段*/
    char lenth1[11];
    char sqlcount[10]; /*从数据库查询的机器总数*/
    char sqltype[10]; /*从数据库中查询到得type值*/
    char typetable[4][10];
    char sqlid[11]; /**sql的id*/
    char sqlid2[11];
    char sqlid3[11];
    char sqlid4[11];
    char sqlid5[11];
    char sqlid6[11];
    char sqlid7[11];
    char sqlid8[11];
    char sqlid9[11];
    char sqlid10[11];
    char sqlid11[11];
    char sqlid12[11];
    char sqlid13[11];
    char sqlid14[11];
    char sqlid15[11];
    char sqlid16[11];
    char sqlid17[11];
    char sqlid18[11];
    char sqlid19[11];
    char sqlid20[11];
    char sqlid21[11];
    char selectid[11];
    char maxNum[10];/*从数据库中查的最大机器编号*/
    char *logname = "auto_reg.txt";
    int loglen = strlen(logname);
    fromdbKey   = ftok(".", 'p'); /*读数据库的消息队列*/
    todbKey     = ftok(".", 'n'); /*写数据库的消息队列*/
    fromtermKey = ftok(".", 'k'); /*接收前台的消息队列*/
    totermKey   = ftok(".", 'l'); /*发送给前台的消息队列*/
    sqlidKey    = ftok(".", 'w'); /*获得sqlid队列*/
    idkey       = ftok(".", 'z'); /*id消息队列*/

    for ( ; ; )
    {
        ipMsg  = (char *) malloc(sizeof(char));
        status = (char *) malloc(sizeof(char));
        if (getconn(fromtermKey, ipMsg, status) > 0)
        {
            /*获得sql语句的id*/
            memset(sqlid, 0, 11);
            rcvfrommsgq(sqlidKey, 0, sqlRes);
            for (i = 0; i < 10; i++)
            {
                sqlid[i] = sqlRes[i];
            }
            sqlid[i] = '\0';
            /*查询数据库表,根据机器的发送过来的ip去搜索id*/
            memset(truesql, 0, 200);
            sprintf(truesql, "select ID from MachineID where IP='%s'", ipMsg);
            log(logname, loglen, truesql, strlen(truesql));
            sprintf(sql, "%s0000000001%010d%s", sqlid, strlen(truesql),
                    truesql);
            log(logname, loglen, sql, strlen(sql));
            sendtodb(sql, todbKey); /*将sql字符数组发送到数据库队列 */
            memset(sqlRes, 0, 512);
            rcvfrommsgq(fromdbKey, atol(sqlid), sqlRes);
            log(logname, loglen, sqlRes, strlen(sqlRes));
            /*解析sql结果中查询的id*/
            for (i = 0; i < 10; i++)
            {
                lenth[i] = sqlRes[i + 20];
            }
            lenth[i] = '\0';
            for (i = 0; i < atoi(lenth); i++)
            {
                selectid[i] = sqlRes[i + 30];
            }
            selectid[i] = '\0';
            /*解析id结束*/
            if ((atoi(selectid)) == 0) /*没有查询到该ip地址的id*/
            {
                /*给机器依次分配机器号*/
                /* 查询数据库中机器编号的max值*/
                memset(sqlid2, 0, 11);
                rcvfrommsgq(sqlidKey, 0, sqlRes);
                for (i = 0; i < 10; i++)
                {
                    sqlid2[i] = sqlRes[i];
                }
                sqlid2[10] = '\0';
                memset(truesql, 0, 200);
                sprintf(truesql, "select MAX(ID) from MachineID");
                log(logname, loglen, truesql, strlen(truesql));
                sprintf(sql, "%s0000000001%010d%s", sqlid2, strlen(truesql),
                        truesql);
                log(logname, loglen, sql, strlen(sql));
                sendtodb(sql, todbKey); /*将sql字符数组发送到数据库队列 */
                memset(sqlRes, 0, 512);
                rcvfrommsgq(fromdbKey, atol(sqlid2), sqlRes);
                log(logname, loglen, sqlRes, strlen(sqlRes));
                /*解析sql结果中查询的id*/
                for (i = 0; i < 10; i++)
                {
                    lenth[i] = sqlRes[i + 20];
                }
                lenth[i] = '\0';
                for (i = 0; i < atoi(lenth); i++)
                {
                    maxNum[i] = sqlRes[i + 30];
                }
                maxNum[i] = '\0';
                /*解析id结束*/
                temp.id = atoi(maxNum) + 1; /*将新分配的id存储起来 */
                strcpy(temp.ip, ipMsg);
                for (i = 0; i < 20; i++)
                    if (temp.ip[i] != '#')
                        trueIp[i] = temp.ip[i];
                    else
                        break;
                trueIp[i] = '\0';

                memset(truesql, 0, 200);
                sprintf(truesql,
                        "insert into MachineID (id,ip,status) values(%d,'%s','1');",
                        temp.id, trueIp);
                log(logname, loglen, truesql, strlen(truesql));
                sprintf(sql, "00000000010000000000%010d%s", strlen(truesql),
                        truesql);
                log(logname, loglen, sql, strlen(sql));
                printf(
                    "++++++++++++++insert an id into machineid table+++++++++++++\n");
                sendtodb(sql, todbKey); /*将sql字符数组发送到数据库队列 */
            }
            else
            {
                /*说明数据库中已经有了该ip的id，该机器以前注册过，当天不予重新分配id*/
                temp.id = atoi(selectid); /*将查询到得id存储起来*/
                strcpy(temp.ip, ipMsg);
                for (i = 0; i < 20; i++)
                    if (temp.ip[i] != '#')
                        trueIp[i] = temp.ip[i];
                    else
                        break;
                trueIp[i] = '\0';
                /*由于该机器号已经有id号在数据库中，需要更新该机器的链接状态*/
                memset(truesql, 0, 200);
                sprintf(truesql,
                        "update MachineID set status ='%d' where IP ='%s'",
                        atoi(status), trueIp);
                log(logname, loglen, truesql, strlen(truesql));
                sprintf(sql, "00000000000000000001%010d%s", strlen(truesql),
                        truesql);
                log(logname, loglen, sql, strlen(sql));
                sendtodb(sql, todbKey); /*将sql字符数组发送到数据库队列 */

            }/*end of if ((atoi(selectid)) == 0) and else*/

            sendtoterm(trueIp, temp.id, idkey);
            /*这个地方我们发送的消息队列为idkey   z消息队列*/

            /*查询当前连接机器总数*/
            memset(sqlid7, 0, 10);
            rcvfrommsgq(sqlidKey, 0, sqlRes);
            log(logname, loglen, sqlRes, strlen(sqlRes));
            for (i = 0; i < 10; i++)
            {
                sqlid7[i] = sqlRes[i];
            }
            sqlid7[10] = '\0'; /*获取sqlid*/
            memset(truesql, 0, 200);
            sprintf(truesql, "select count(*) from MachineID where id!=0");
            log(logname, loglen, truesql, strlen(truesql));
            sprintf(sql, "%s0000000001%010d%s", sqlid7, strlen(truesql),
                    truesql);
            log(logname, loglen, sql, strlen(sql));
            sendtodb(sql, todbKey);
            memset(sqlRes, 0, 512);
            rcvfrommsgq(fromdbKey, atol(sqlid7), sqlRes);
            log(logname, loglen, sqlRes, strlen(sqlRes));
            for (i = 0; i < 10; i++)
            {
                lenth[i] = sqlRes[i + 20];
            }
            lenth[i] = '\0';
            for (i = 0; i < atoi(lenth); i++)
            {
                sqlcount[i] = sqlRes[i + 30];
            }
            sqlcount[i] = '\0';
            num = atoi(sqlcount);
            printf("machine count==>%d\n", num);
            idNum = (int *) malloc(sizeof(int) * (num + 1));

            if (num > 1)/*至少有两台机器，才需要生成type表*/
            {
                /*查询数据库,读出当前所有连接在网关上的机器的机器编号*/
                memset(sqlid8, 0, 10);
                rcvfrommsgq(sqlidKey, 0, sqlRes);
                log(logname, loglen, sqlRes, strlen(sqlRes));
                for (i = 0; i < 10; i++)
                {
                    sqlid8[i] = sqlRes[i];
                }
                sqlid8[10] = '\0'; /*获取sqlid*/
                memset(truesql, 0, 200);
                sprintf(truesql, "select ID from MachineID where id!=0");
                log(logname, loglen, truesql, strlen(truesql));
                sprintf(sql, "%s0000000001%010d%s", sqlid8, strlen(truesql),
                        truesql);
                log(logname, loglen, sql, strlen(sql));
                sendtodb(sql, todbKey);
                /*这里循环接收num次，将返回的num个结果存储在数组中*/
                for (i = 0; i < num; i++) /*begin of for D*/
                {
                    memset(sqlRes, 0, 512);
                    rcvfrommsgq(fromdbKey, atol(sqlid8), sqlRes);
                    log(logname, loglen, sqlRes, strlen(sqlRes));
                    for (j = 0; j < 10; j++)
                    {
                        lenth[j] = sqlRes[j + 20];
                    }
                    lenth[j] = '\0';
                    for (j = 0; j < atoi(lenth); j++)
                    {
                        sqlcount[j] = sqlRes[j + 30];
                    }
                    sqlcount[j] = '\0';
                    idNum[i] = atoi(sqlcount);
                }/*end of for D */
                /*根据所有连接在网关上的机器的机器编号生成type表*/
                /*查询数据库中type1表和type2表type值去大者*/
                memset(sqlid9, 0, 10);
                rcvfrommsgq(sqlidKey, 0, sqlRes);
                log(logname, loglen, sqlRes, strlen(sqlRes));
                for (i = 0; i < 10; i++)
                {
                    sqlid9[i] = sqlRes[i];
                }
                sqlid9[10] = '\0'; /*获取sqlid*/
                memset(truesql, 0, 200);
                sprintf(truesql, "select MAX(id) from type1");
                log(logname, loglen, truesql, strlen(truesql));
                sprintf(sql, "%s0000000001%010d%s", sqlid9, strlen(truesql),
                        truesql);
                log(logname, loglen, sql, strlen(sql));
                sendtodb(sql, todbKey);
                memset(sqlRes, 0, 512);
                rcvfrommsgq(fromdbKey, atol(sqlid9), sqlRes);
                log(logname, loglen, sqlRes, strlen(sqlRes));
                for (i = 0; i < 10; i++)
                {
                    lenth[i] = sqlRes[i + 20];
                }
                lenth[i] = '\0';
                for (i = 0; i < atoi(lenth); i++)
                {
                    sqltype[i] = sqlRes[i + 30];
                }
                sqltype[i] = '\0';
                typeNum1 = atoi(sqltype);
                memset(sqlid10, 0, 10);
                rcvfrommsgq(sqlidKey, 0, sqlRes);
                log(logname, loglen, sqlRes, strlen(sqlRes));
                for (i = 0; i < 10; i++)
                {
                    sqlid10[i] = sqlRes[i];
                }
                sqlid10[10] = '\0'; /*获取sqlid*/
                memset(truesql, 0, 200);
                sprintf(truesql, "select MAX(id) from type2");
                log(logname, loglen, truesql, strlen(truesql));
                sprintf(sql, "%s0000000001%010d%s", sqlid10, strlen(truesql),
                        truesql);
                log(logname, loglen, sql, strlen(sql));
                sendtodb(sql, todbKey);
                memset(sqlRes, 0, 512);
                rcvfrommsgq(fromdbKey, atol(sqlid10), sqlRes);
                log(logname, loglen, sqlRes, strlen(sqlRes));
                for (i = 0; i < 10; i++)
                {
                    lenth[i] = sqlRes[i + 20];
                }
                lenth[i] = '\0';
                for (i = 0; i < atoi(lenth); i++)
                {
                    sqltype[i] = sqlRes[i + 30];
                }
                sqltype[i] = '\0';
                typeNum2 = atoi(sqltype);

                typeNum = typeNum1 > typeNum2 ? typeNum1 : typeNum2;
                msg1 = (struct TypeMsg1 *) malloc(
                           sizeof(struct TypeMsg1) * (num * 2 + 1));
                type1(msg1, idNum, num, typeNum);/*生成1：1的type表*/
                for (i = 0; i < (num - 1) * 2; i++) /*将新生成的1：1type值插入数据库中的type表*/
                {
                    memset(sqlid11, 0, 10);
                    rcvfrommsgq(sqlidKey, 0, sqlRes);
                    for (j = 0; j < 10; j++)
                    {
                        sqlid11[j] = sqlRes[j];
                    }
                    sqlid11[10] = '\0'; /*获取sqlid*/
                    memset(truesql, 0, 200);
                    sprintf(truesql,
                            "insert into type1 (source,destination,type,id) values('%d','%d','type%d',%d)",
                            msg1[i].sourceID, msg1[i].destinationID,
                            msg1[i].type, msg1[i].type);
                    log(logname, loglen, truesql, strlen(truesql));
                    sprintf(sql, "%s0000000000%010d%s", sqlid11,
                            strlen(truesql), truesql);
                    log(logname, loglen, sql, strlen(sql));
                    sendtodb(sql, todbKey);
                    printf(
                        "send type 1 to 1 todb is ok ============++++>>>>>>\n");
                }
                free(msg1);
            } /* end if(num >1) */
            if (num > 2) /*至少有三台机器，则需要生成1：2的type表*/
            {
                /*查询数据库中type1表中type值已经分配到了何处*/
                memset(sqlid12, 0, 10);
                rcvfrommsgq(sqlidKey, 0, sqlRes);
                log(logname, loglen, sqlRes, strlen(sqlRes));
                for (i = 0; i < 10; i++)
                {
                    sqlid12[i] = sqlRes[i];
                }
                sqlid12[10] = '\0'; /*获取sqlid*/
                memset(truesql, 0, 200);
                sprintf(truesql, "select MAX(id) from type1");
                log(logname, loglen, truesql, strlen(truesql));
                sprintf(sql, "%s0000000001%010d%s", sqlid12, strlen(truesql),
                        truesql);
                log(logname, loglen, sql, strlen(sql));
                sendtodb(sql, todbKey);
                memset(sqlRes, 0, 512);
                rcvfrommsgq(fromdbKey, atol(sqlid12), sqlRes);
                log(logname, loglen, sqlRes, strlen(sqlRes));
                for (i = 0; i < 10; i++)
                {
                    lenth[i] = sqlRes[i + 20];
                }
                lenth[i] = '\0';
                for (i = 0; i < atoi(lenth); i++)
                {
                    sqltype[i] = sqlRes[i + 30];
                }
                sqltype[i] = '\0';
                typeNum1 = atoi(sqltype);

                memset(sqlid13, 0, 10);
                rcvfrommsgq(sqlidKey, 0, sqlRes);
                log(logname, loglen, sqlRes, strlen(sqlRes));
                for (i = 0; i < 10; i++)
                {
                    sqlid13[i] = sqlRes[i];
                }
                sqlid13[10] = '\0'; /*获取sqlid*/
                memset(truesql, 0, 200);
                sprintf(truesql, "select MAX(id) from type2");
                log(logname, loglen, truesql, strlen(truesql));
                sprintf(sql, "%s0000000001%010d%s", sqlid13, strlen(truesql),
                        truesql);
                log(logname, loglen, sql, strlen(sql));
                sendtodb(sql, todbKey);
                memset(sqlRes, 0, 512);
                rcvfrommsgq(fromdbKey, atol(sqlid13), sqlRes);
                log(logname, loglen, sqlRes, strlen(sqlRes));
                for (i = 0; i < 10; i++)
                {
                    lenth[i] = sqlRes[i + 20];
                }
                lenth[i] = '\0';
                for (i = 0; i < atoi(lenth); i++)
                {
                    sqltype[i] = sqlRes[i + 30];
                }
                sqltype[i] = '\0';
                typeNum2 = atoi(sqltype);
                typeNum = typeNum1 > typeNum2 ? typeNum1 : typeNum2;
                msg2 = (struct TypeMsg2 *) malloc(
                           sizeof(struct TypeMsg2) * (num * (num - 1) * 3 + 1));
                type2(msg2, idNum, num, typeNum);
                for (i = 0; i < (num - 1) * (num - 2) * 3; i++)
                {
                    memset(sqlid14, 0, 10);
                    rcvfrommsgq(sqlidKey, 0, sqlRes);
                    for (j = 0; j < 10; j++)
                    {
                        sqlid14[j] = sqlRes[j];
                    }
                    sqlid14[10] = '\0'; /*获取sqlid*/
                    memset(truesql, 0, 200);
                    sprintf(truesql,
                            "insert into type2 (source,destination1,destination2,type,id) values('%d','%d','%d','type%d',%d)",
                            msg2[i].sourceID, msg2[i].destinationID1,
                            msg2[i].destinationID2, msg2[i].type, msg2[i].type);
                    log(logname, loglen, truesql, strlen(truesql));
                    sprintf(sql, "%s0000000000%010d%s", sqlid14,
                            strlen(truesql), truesql);
                    log(logname, loglen, sql, strlen(sql));
                    sendtodb(sql, todbKey);
                    printf("send to 1 to 2 type is ok ==========>>>>>>>>>>>");
                }/*end of for i*/
                free(msg2); //测试的时候并没有测试这一段
            }/*end if(num>2)*/
            free(idNum); /*释放内存空间*/
            memset(sqlid15, 0, 10);
            rcvfrommsgq(sqlidKey, 0, sqlRes);
            log(logname, loglen, sqlRes, strlen(sqlRes));
            for (i = 0; i < 10; i++)
            {
                sqlid15[i] = sqlRes[i];
            }
            sqlid15[10] = '\0';/*获取sqlid*/
            memset(truesql, 0, 200);
            sprintf(truesql, "select count(*) from MachineID where id!=0");
            log(logname, loglen, truesql, strlen(truesql));
            sprintf(sql, "%s0000000001%010d%s", sqlid15, strlen(truesql),
                    truesql);
            log(logname, loglen, sql, strlen(sql));
            sendtodb(sql, todbKey);
            memset(sqlRes, 0, 512);
            rcvfrommsgq(fromdbKey, atol(sqlid15), sqlRes);
            log(logname, loglen, sqlRes, strlen(sqlRes));
            for (i = 0; i < 10; i++)
            {
                lenth[i] = sqlRes[i + 20];
            }
            lenth[i] = '\0';
            for (i = 0; i < atoi(lenth); i++)
            {
                sqlcount[i] = sqlRes[i + 30];
            }
            sqlcount[i] = '\0';
            num = atoi(sqlcount);
            printf("select count(*) ok ==============num=%d=>>>>>>>>>>>>\n",
                   num);
            /*查询数据库中当前连在网关的所有机器ip,向所有机器发送1：1type表*/
            if (num > 1)
            {
                memset(sqlid16, 0, 10);
                rcvfrommsgq(sqlidKey, 0, sqlRes);
                log(logname, loglen, sqlRes, strlen(sqlRes));
                for (i = 0; i < 10; i++)
                {
                    sqlid16[i] = sqlRes[i];
                }
                sqlid16[10] = '\0';/*获取sqlid*/
                memset(truesql, 0, 200);
                sprintf(truesql, "select ID from MachineID where id!=0");
                log(logname, loglen, truesql, strlen(truesql));
                sprintf(sql, "%s0000000001%010d%s", sqlid16, strlen(truesql),
                        truesql);
                log(logname, loglen, sql, strlen(sql));
                sendtodb(sql, todbKey);
                printf("select ID  1 to 1 is ok ===============>>>>>>>>>>>>\n");

                idNum = (int *) malloc(sizeof(int) * (num + 1));
                for (i = 0; i < num; i++)
                {
                    printf("num = %d\n", num);
                    memset(sqlRes, 0, 512);
                    rcvfrommsgq(fromdbKey, atol(sqlid16), sqlRes);
                    log(logname, loglen, sqlRes, strlen(sqlRes));
                    for (j = 0; j < 10; j++)
                    {
                        lenth[j] = sqlRes[j + 20];
                    }
                    lenth[j] = '\0';
                    for (j = 0; j < atoi(lenth); j++)
                    {
                        id[j] = sqlRes[j + 30];
                    }
                    id[j] = '\0';
                    idNum[i] = atoi(id);
                    memset(sqlid17, 0, 10);
                    rcvfrommsgq(sqlidKey, 0, sqlRes);
                    log(logname, loglen, sqlRes, strlen(sqlRes));
                    for (j = 0; j < 10; j++)
                    {
                        sqlid17[j] = sqlRes[j];
                    }
                    sqlid17[10] = '\0';/*获取sqlid*/
                    memset(truesql, 0, 200);
                    sprintf(truesql, "select IP from MachineID where ID=%d",
                            idNum[i]);
                    log(logname, loglen, truesql, strlen(truesql));
                    sprintf(sql, "%s0000000001%010d%s", sqlid17,
                            strlen(truesql), truesql);
                    log(logname, loglen, sql, strlen(sql));
                    sendtodb(sql, todbKey);
                    memset(sqlRes, 0, 512);
                    rcvfrommsgq(fromdbKey, atol(sqlid17), sqlRes);
                    log(logname, loglen, sqlRes, strlen(sqlRes));
                    for (j = 0; j < 10; j++)
                    {
                        lenth[j] = sqlRes[j + 20];
                    }
                    for (j = 0; j < atoi(lenth); j++)
                    {
                        ip[j] = sqlRes[j + 30];
                    }
                    ip[j] = '\0';
                    printf("ip is +++++++++++++.>>>>>>>>>>>>>%s\n", ip);

                    memset(sqlid18, 0, 10);
                    rcvfrommsgq(sqlidKey, 0, sqlRes);
                    log(logname, loglen, sqlRes, strlen(sqlRes));
                    for (j = 0; j < 10; j++)
                    {
                        sqlid18[j] = sqlRes[j];
                    }
                    sqlid18[10] = '\0';/*获取sqlid*/
                    memset(truesql, 0, 200);
                    sprintf(truesql, "select source,destination,id from type1");
                    log(logname, loglen, truesql, strlen(truesql));
                    sprintf(sql, "%s0000000003%010d%s", sqlid18,
                            strlen(truesql), truesql);
                    log(logname, loglen, sql, strlen(sql));
                    sendtodb(sql, todbKey);
                    //    msg1=NULL;
                    msg1 = (struct TypeMsg1 *) malloc(
                               sizeof(struct TypeMsg1) * (num * (num - 1) + 1));
                    for (j = 0; j < num * (num - 1); j++)
                    {
                        int start = 20;
                        char len[11];
                        /*查询数据库的type表,向所有连接在网关上的机器发送type信息表*/
                        memset(sqlRes, 0, 512);
                        rcvfrommsgq(fromdbKey, atol(sqlid18), sqlRes);
                        log(logname, loglen, sqlRes, strlen(sqlRes));
                        /*   printf("数据库返回1:1的结果是=+==========>:>>>>>>>>%s\n",sqlRes);*/
                        for (k = 0; k < 10; k++)
                        {
                            lenth[k] = sqlRes[k + 10];
                        }
                        lenth[k] = '\0';
                        for (k = 0; k < atoi(lenth); k++) /*需要解析的字段的个数*/
                        {
                            int w;
                            char templen[11];
                            for (w = 0; w < 10; w++)
                                templen[w] = sqlRes[start + w];
                            templen[w] = '\0';
                            start = start + 10;
                            for (w = 0; w < atoi(templen); w++)
                                len[w] = sqlRes[w + start];
                            len[w] = '\0';
                            start = start + strlen(len);
                            strcpy(typetable[k], len);
                            /*   printf("type===??????......>>>>>>>>%s\n",typetable[k]);*/
                        }
                        msg1[j].sourceID = atoi(typetable[0]);
                        msg1[j].destinationID = atoi(typetable[1]);
                        msg1[j].type = atoi(typetable[2]);
                        /*
                         printf("source is %s\n destination is %s\n type is %s\n",typetable[0],typetable[1],typetable[2]);
                         */
                        sendtype1(ip, msg1[j], totermKey); /*先发送1：1的type表*/
                        printf("here 1 to 1 is good===++++++>>>>>>>\n");
                        /*  printf("source is %d\n destination is %d\n type is %d\n",msg1[j].sourceID,msg1[j].destinationID,msg1[j].type);*/
                    } /*end for(j<num*(num-1)) */
                    free(msg1);
                }/*end for(i>num)) */
                free(idNum);
            } /*End if(num >1) */
            if (num > 2)
            {
                memset(sqlid19, 0, 11);
                rcvfrommsgq(sqlidKey, 0, sqlRes);
                printf("****************shiguiling:%s\n*********", sqlRes);
                for (i = 0; i < 10; i++)
                {
                    sqlid19[i] = sqlRes[i];
                }
                sqlid19[10] = '\0';/*获取sqlid*/
                printf("sql19 is @@@@@@@@@@@@@@:%s\n", sqlid19);
                memset(truesql, 0, 200);
                sprintf(truesql, "select ID from MachineID where id!=0");
                sprintf(sql, "%s0000000001%010d%s", sqlid19, strlen(truesql),
                        truesql);
                sendtodb(sql, todbKey);
                printf("************************begin first pause\n");
                printf("***first pause***\n");
                idNum = (int *) malloc(sizeof(int) * (num + 1));
                for (i = 0; i < num; i++)
                {
                    memset(sqlRes, 0, 512);
                    rcvfrommsgq(fromdbKey, atol(sqlid19), sqlRes);
                    printf("get one id ***###############%s,%x\n", sqlRes,
                           fromdbKey);
                    for (j = 0; j < 10; j++)
                    {
                        lenth[j] = sqlRes[j + 20];
                    }
                    lenth[j] = '\0';
                    for (j = 0; j < atoi(lenth); j++)
                    {
                        id[j] = sqlRes[j + 30];
                    }
                    id[j] = '\0';
                    idNum[i] = atoi(id);
                    in("573\n");
                    printf("select id 1 to 2+++++==========>>>>>>>>>>>\n");
                    memset(sqlid20, 0, 10);
                    rcvfrommsgq(sqlidKey, 0, sqlRes);
                    for (j = 0; j < 10; j++)
                    {
                        sqlid20[j] = sqlRes[j];
                    }
                    sqlid20[10] = '\0';/*获取sqlid*/
                    memset(truesql, 0, 200);
                    sprintf(truesql, "select IP from MachineID where ID=%d",
                            idNum[i]);
                    sprintf(sql, "%s0000000001%010d%s", sqlid20,
                            strlen(truesql), truesql);
                    sendtodb(sql, todbKey);
                    memset(sqlRes, 0, 512);
                    rcvfrommsgq(fromdbKey, atol(sqlid20), sqlRes);
                    printf("***********shguiling@@@%s\n", sqlRes);
                    for (j = 0; j < 10; j++)
                    {
                        lenth[j] = sqlRes[j + 20];
                    }
                    for (j = 0; j < atoi(lenth); j++)
                    {
                        ip[j] = sqlRes[j + 30];
                    }
                    ip[j] = '\0';
                    printf("here ip is ok ------------->>>>>>>>>>>\n");
                    /*         printf("ip is +++++++++++++.>>>>>>>>>>>>>%s\n",ip);*/
                    memset(sqlid21, 0, 10);
                    rcvfrommsgq(sqlidKey, 0, sqlRes);
                    for (j = 0; j < 10; j++)
                    {
                        sqlid21[j] = sqlRes[j];
                    }
                    sqlid21[10] = '\0';/*获取sqlid*/
                    memset(truesql, 0, 200);
                    sprintf(truesql,
                            "select source,destination1,destination2,id from type2");
                    sprintf(sql, "%s0000000004%010d%s", sqlid21,
                            strlen(truesql), truesql);
                    sendtodb(sql, todbKey);
                    msg2 = (struct TypeMsg2 *) malloc(
                               sizeof(struct TypeMsg2)
                               * ((num * (num - 1) * (num - 2)) + 1));
                    for (j = 0; j < num * (num - 1) * (num - 2); j++)
                    {
                        int start = 20;
                        char len[10];
                        /*查询数据库的type表,向所有连接在网关上的机器发送type信息表*/
                        memset(sqlRes, 0, 512);
                        rcvfrommsgq(fromdbKey, atol(sqlid21), sqlRes);
                        /*      printf("数据库返回1:2的结果是=+==========>:>>>>>>>>%s\n",sqlRes);*/
                        for (k = 0; k < 10; k++)
                        {
                            lenth[k] = sqlRes[k + 10];
                        }
                        lenth[k] = '\0';
                        for (k = 0; k < atoi(lenth); k++) /*需要解析的字段的个数*/
                        {
                            int w;
                            char templen[11];
                            for (w = 0; w < 10; w++)
                                templen[w] = sqlRes[start + w];
                            templen[w] = '\0';
                            start = start + 10;
                            for (w = 0; w < atoi(templen); w++)
                                len[w] = sqlRes[w + start];
                            len[w] = '\0';
                            start = start + strlen(len);
                            strcpy(typetable[k], len);
                            /*  printf("type===??????......>>>>>>>>%s\n",typetable[k]);*/
                        }/*
						 printf("source is %s\n destination1 is %s\n destination2 is %s\n  type is %s\n",typetable[0],typetable[1],typetable[2],typetable[3]);
						 */
                        msg2[j].sourceID = atoi(typetable[0]);
                        msg2[j].destinationID1 = atoi(typetable[1]);
                        msg2[j].destinationID2 = atoi(typetable[2]);
                        msg2[j].type = atoi(typetable[3]);
                        printf("here 1 to 2 is good===++++++>>>>>>>\n");
                        sendtype2(ip, msg2[j], totermKey);
                        /*后发送1：2的type表*/
                    }
                    free(msg2);
                }
                free(idNum);
            }
            printf(" ++++in loop++++++\n");
        }/*end if(getconn)*/
    }
}


#endif // AUTO_REG_H_INCLUDED
