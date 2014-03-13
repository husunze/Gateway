/*
 * AESmain.c
 *
 *  Created on: 2013年8月10日
 *      Author: oracle
 */

#include "AESmain.h"

void encrpt(unsigned char* in,unsigned char* key,char *out2)
{
    int i;
    AES_U8 out[16];
    AES_Encrypt (in, key, out);
    for(i=0; i<16; i++)
        out2[i]=out[i];

}

void decrpt(unsigned char* out,unsigned char* key,char* out2)
{
    int i;
    AES_U8 in[16];
    AES_Decrypt (out, key, in);
    for(i=0; i<16; i++)
    {
        out2[i]=in[i];
    }

}

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

