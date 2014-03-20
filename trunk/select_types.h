/*
 * select_types.h
 *
 *  Created on: 2013年8月13日
 *      Author: oracle
 */

#ifndef SELECT_TYPES_H_
#define SELECT_TYPES_H_

#include <stdio.h>
#include "csh_common_functions.h"
#include "id_to_ip.h"
#include "csh_type_def.h"

void select_type2_byname(char type_name[],struct pathtype* yourtype);
void select_type1_byname(char type_name[],struct pathtype* yourtype);


#endif /* SELECT_TYPES_H_ */
