/*
 * sendtoterm.h
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */

#ifndef SENDTOTERM_H_
#define SENDTOTERM_H_

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"config.h"

void sendtoterm(char *ip, int id, key_t key);

#endif /* SENDTOTERM_H_ */
