/*
 * sendtype.h
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */

#ifndef SENDTYPE_H_
#define SENDTYPE_H_

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"config.h"

void sendtype1(char *ip, struct TypeMsg1 s1, key_t key);

void sendtype2(char *ip, struct TypeMsg2 s2, key_t key);

#endif /* SENDTYPE_H_ */
