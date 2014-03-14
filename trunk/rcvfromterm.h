/*
 * rcvfromterm.h
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */

#ifndef RCVFROMTERM_H_
#define RCVFROMTERM_H_

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"config.h"

void rcvfromterm(key_t key);

#endif /* RCVFROMTERM_H_ */
