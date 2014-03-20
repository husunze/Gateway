/*
 * AESmain.h
 *
 *  Created on: 2013年8月10日
 *      Author: oracle
 */

#ifndef AESMAIN_H_
#define AESMAIN_H_
#include <stdio.h>
#include <stdlib.h>
#include "AES_lib.h"

void encrpt(unsigned char* in,unsigned char* key,char *out2);

void decrpt(unsigned char* out,unsigned char* key,char* out2);

//int main()
//{
//    int i;
//    char in[]="1234567890123456";
//    char out[16];
//    char key[16]="1234567890123456";
//    encrpt(in,key,out);
//    for(i=0;i<16;i++)
//    {
//        printf("%c ",out[i]);
//    }
//    printf("\n");
//    decrpt(out,key,in);
//    for(i=0;i<16;i++)
//    {
//        printf("%c ",in[i]);
//    }
//    printf("\n");
//}


#endif /* AESMAIN_H_ */
