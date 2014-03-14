/*
 * gettype.c
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */

#include "gettype.h"

void type1(struct TypeMsg1 *msg1, int *num, int len, int type)
{
    int i;
    int k = 0;
    /*新分配的机器在第一个位置*/
    for (i = 0; i < len - 1; i++)
    {
        msg1[k].sourceID = num[len - 1];
        msg1[k].destinationID = num[i];
        msg1[k].type = ++type;
        k++;
    }
    /*新分配的机器在第二个位置*/
    for (i = 0; i < len - 1; i++)
    {
        msg1[k].sourceID = num[i];
        msg1[k].destinationID = num[len - 1];
        msg1[k].type = ++type;
        k++;
    }
    return;
}

void type2(struct TypeMsg2 *msg2, int *num, int len, int type)
{
    int i, j;
    int k = 0;
    /*新分配的机器在第一个位置*/
    for (i = 0; i < len - 1; i++)
        for (j = 0; j < len - 1; j++)
        {
            if (num[i] == num[j])
                continue;
            msg2[k].sourceID = num[len - 1];
            msg2[k].destinationID1 = num[i];
            msg2[k].destinationID2 = num[j];
            msg2[k].type = ++type;
            k++;
        }

    /*新分配的机器在中间位置*/
    for (i = 0; i < len - 1; i++)
        for (j = 0; j < len - 1; j++)
        {
            if (num[i] == num[j])
                continue;
            msg2[k].sourceID = num[i];
            msg2[k].destinationID1 = num[len - 1];
            msg2[k].destinationID2 = num[j];
            msg2[k].type = ++type;
            k++;
        }

    /*新分配的机器在最后的位置*/
    for (i = 0; i < len - 1; i++)
        for (j = 0; j < len - 1; j++)
        {
            if (num[i] == num[j])
                continue;
            msg2[k].sourceID = num[i];
            msg2[k].destinationID1 = num[j];
            msg2[k].destinationID2 = num[len - 1];
            msg2[k].type = ++type;
            k++;
        }
    return;
}

