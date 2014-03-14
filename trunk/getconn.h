/*
 * getconn.h
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */

#ifndef GETCONN_H_
#define GETCONN_H_

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include"config.h"

int getconn(key_t key, char* ipMsg, char* status);

#endif /* GETCONN_H_ */
