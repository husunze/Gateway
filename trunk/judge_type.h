/*
 * judge_type.h
 *
 *  Created on: 2013年8月13日
 *      Author: oracle
 */

#ifndef JUDGE_TYPE_H_
#define JUDGE_TYPE_H_

#include <stdio.h>
#include "csh_common_functions.h"

void judge_type_byname(char type_name[],char result[]);
/*
main(){
	char a[]="type10";
	char b[20];
	judge_type_byname(a,b);
	printf("======================> result: %s\n",b);
}*/

#endif /* JUDGE_TYPE_H_ */
