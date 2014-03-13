/*
 * mysql.c
 *
 *  Created on: 2013年8月8日
 *      Author: oracle
 */

#ifndef MYSQL_C_
#define MYSQL_C_

#include <mysql/mysql.h>
#include <stdlib.h>
#include "error.h"

#define server "localhost"
#define user "root"
#define password "xA123456"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
char *database = "localdb";
char *logname = "mysql.txt";
char sql[100];
char findkey[20];

//检查IP是否在trust表里面存在，存在则返回1不存在返回0
int checkIP(char IP[])
{
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
                            0))
    {
        char *message = mysql_errno(conn);
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_real_connect error!");
        exit(1);
    }
    sprintf(sql, "select count(*) from trust where IP='%s'", IP);
    log(logname, strlen(logname), sql, strlen(sql));
    if (mysql_query(conn, sql))
    {
        char *message = mysql_errno(conn);
        log(logname, strlen(logname), message, strlen(message));
        message = "mysql_query_error!";
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_query_error!");
        exit(1);
    }
    res = mysql_use_result(conn);
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%s\n", row[0]);
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }
    mysql_free_result(res);
    mysql_close(conn);
    return 0;

}
//插入IP和key进入trustKey表，成功返回1，失败返回0
int key_ip_in(char key[], char IP[])
{
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
                            0))
    {
        char *message = mysql_errno(conn);
        log(logname, strlen(logname), message, strlen(message));
        message = "mysql_real_connect error!";
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_real_connect error!");
        mysql_close(conn);
        return 0;
        //  exit(1);
    }
    sprintf(sql, "insert into TrustKey values('%s','%s')", IP, key);
    log(logname, strlen(logname), sql, strlen(sql));
    if (!(res = (mysql_query(conn, sql))))
    {
        printf("inserted %lu rows\n",
               (unsigned long) mysql_affected_rows(conn));
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }
    else
    {
        char *message = mysql_error(conn);
        log(logname, strlen(logname), message, strlen(message));
        message = "mysql_query_error";
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_query_error!");
    }

    mysql_close(conn);
    return 0;

}
//把IP和key插入受信任的trust表里面
int IP_KEY_in(char IP[], char key[])
{
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
                            0))
    {
        char *message = mysql_errno(conn);
        log(logname, strlen(logname), message, strlen(message));
        message = "mysql_real_connect error!";
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_real_connect error!");
        exit(1);
    }
    sprintf(sql, "insert into trust values('%s','%s')", IP, key);
    log(logname, strlen(logname), sql, strlen(sql));
    if (!(res = (mysql_query(conn, sql))))
    {
        printf("inserted %lu rows\n",
               (unsigned long) mysql_affected_rows(conn));
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }
    else
    {
        char *message = mysql_error(conn);
        log(logname, strlen(logname), message, strlen(message));
        message = "mysql_query_error!";
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_query_error!");
        //  exit(1);
    }
    //  mysql_free_result(res);
    mysql_close(conn);
    return 0;

}
//通过IP查找key，成功则返回key指针，失败返回NULL
char *IP_find_key(char IP[])
{
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
                            0))
    {
        char *message = mysql_errno(conn);
        log(logname, strlen(logname), message, strlen(message));
        message = "mysql_real_connect error!";
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_real_connect error!");
        exit(1);
    }
    sprintf(sql, "select skey from TrustKey where IP='%s'", IP);
    log(logname, strlen(logname), sql, strlen(sql));
    //   printf("OK115!\n");
    if (mysql_query(conn, sql))
    {
        char *message = mysql_error(conn);
        log(logname, strlen(logname), message, strlen(message));
        message = "mysql_query_error!";
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_query_error!");
        exit(1);
    }
    res = mysql_use_result(conn);
    //   printf("OK122!\n");
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        //       printf("OK124!\n");
        strcpy(findkey, row[0]);
        mysql_free_result(res);
        mysql_close(conn);
        printf("%s\n", findkey);
        return (char *) &findkey;
    }
    //   printf("OK125!\n");
    mysql_free_result(res);
    mysql_close(conn);
    perror("db error!");
    //   exit(1);
    return NULL;

}

//通过IP查找初始key，成功则返回key指针，失败返回NULL
char *IP_find_key_again(char IP[])
{
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
                            0))
    {
        char *message = mysql_errno(conn);
        log(logname, strlen(logname), message, strlen(message));
        message = "mysql_real_connect error!";
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_real_connect error!");
        exit(1);
    }
    sprintf(sql, "select SKEY from trust where IP='%s'", IP);
    log(logname, strlen(logname), sql, strlen(sql));
    //   printf("OK115!\n");
    if (mysql_query(conn, sql))
    {
        char *message = mysql_error(conn);
        log(logname, strlen(logname), message, strlen(message));
        message = "mysql_query_error!";
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_query_error!");
        exit(1);
    }
    res = mysql_use_result(conn);
    //   printf("OK122!\n");
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        //       printf("OK124!\n");
        strcpy(findkey, row[0]);
        mysql_free_result(res);
        mysql_close(conn);
        //     printf("%s\n",findkey);
        return (char *) &findkey;
    }
    //   printf("OK125!\n");
    mysql_free_result(res);
    mysql_close(conn);
    perror("db error!");
    // exit(1);
    return NULL;

}

//清空表TrustKey,成功返回1，失败返回0
int clean_TrustKey()
{
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
                            0))
    {
        char *message = mysql_errno(conn);
        log(logname, strlen(logname), message, strlen(message));
        message = "mysql_real_connect error!";
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_real_connect error!");
        exit(1);
    }
    sprintf(sql, "delete from TrustKey");
    log(logname, strlen(logname), sql, strlen(sql));
    if (!(res = (mysql_query(conn, sql))))
    {
        printf("delete %lu rows\n", (unsigned long) mysql_affected_rows(conn));
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }
    else
    {
        char *message = mysql_error(conn);
        log(logname, strlen(logname), message, strlen(message));
        message = "mysql_query_error!";
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_query_error!");
        exit(1);
    }
    mysql_free_result(res);
    mysql_close(conn);
    return 0;

}

//通过IP删除一行数据
int del_IP_KEY(char IP[])
{
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
                            0))
    {
        char *message = mysql_errno(conn);
        log(logname, strlen(logname), message, strlen(message));
        message = "mysql_real_connect error!";
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_real_connect error!");
        exit(1);
    }
    sprintf(sql, "delete from trust where IP='%s';", IP);
    log(logname, strlen(logname), sql, strlen(sql));
    if (!(res = (mysql_query(conn, sql))))
    {
        printf("delete %lu rows\n", (unsigned long) mysql_affected_rows(conn));
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }
    else
    {
        char *message = mysql_error(conn);
        log(logname, strlen(logname), message, strlen(message));
        message = "mysql_query_error!";
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_query_error!");
        exit(1);
    }
    mysql_free_result(res);
    mysql_close(conn);
    return 0;

}

//通过IP修改一行数据
int alter_IP_KEY(char IP[], char key[])
{
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL,
                            0))
    {
        char *message = mysql_errno(conn);
        log(logname, strlen(logname), message, strlen(message));
        message = "mysql_real_connect error!";
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_real_connect error!");
        exit(1);
    }
    sprintf(sql, "update trust set SKEY='%s' where IP='%s'", key, IP);
    log(logname, strlen(logname), sql, strlen(sql));
    if (!(res = (mysql_query(conn, sql))))
    {
        printf("update %lu rows\n", (unsigned long) mysql_affected_rows(conn));
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }
    else
    {
        char *message = mysql_error(conn);
        log(logname, strlen(logname), message, strlen(message));
        message = "mysql_query_error!";
        log(logname, strlen(logname), message, strlen(message));
        perror("mysql_query_error!");
        exit(1);
    }
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}

#endif /* MYSQL_C_ */
