/*
 * rcvfrommsgq.h
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */

#ifndef RCVFROMMSGQ_H_
#define RCVFROMMSGQ_H_

#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"config.h"

void rcvfrommsgq(key_t key, long type, char* sqlRes);

#endif /* RCVFROMMSGQ_H_ */
