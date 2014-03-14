/*
 * sendtodb.h
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */

#ifndef SENDTODB_H_
#define SENDTODB_H_

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"config.h"

void sendtodb(char *s, key_t key);

#endif /* SENDTODB_H_ */
