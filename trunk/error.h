/*
 * error.h
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */

#ifndef ERROR_H_
#define ERROR_H_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FLAGS  O_WRONLY | O_CREAT | O_APPEND
#define MODE  S_IRWXU | S_IRGRP | S_IXGRP |S_IROTH | S_IXOTH

int in(char ch[]);
void log(char *name, int namelen, char *message, int messagelen);

#endif /* ERROR_H_ */
