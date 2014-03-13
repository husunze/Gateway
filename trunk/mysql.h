/*
 * mysql.h
 *
 *  Created on: 2013年8月7日
 *      Author: oracle
 */

#ifndef MYSQL_H_
#define MYSQL_H_

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql_use.h"

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

#endif /* MYSQL_H_ */
