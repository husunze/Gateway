/*
 * error.c
 *
 *  Created on: 2013年8月9日
 *      Author: oracle
 */
#include "error.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int in(char ch[]) {
	int fd;
	printf("%s\n", ch);
	/*    if((fd = open("log",FLAGS,MODE))==-1)
	 {
	 printf("error \n");
	 return -1;

	 //    }
	 //    else

	 {
	 write(fd,ch,strlen(ch));
	 }
	 close(fd);*/
	return 0;
}

void log(char *name, int namelen, char *message, int messagelen){
    FILE *fp = NULL;
    char path[300];
    char *ppath = "./";
    time_t rawtime;
    struct tm *timeinfo;
    int pathlen = sizeof(ppath);
    strncpy(path, ppath, pathlen);
    strncat(path, name, namelen);
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    fp = fopen(path, "a+");
    if(fp != NULL){
        fprintf(fp, "%-40s", asctime(timeinfo));
        fprintf(fp, "%*s\n", messagelen, message);
    }
    fclose(fp);
}
/*
int main(){
    char *name = "log1.txt";
    char *message = "this is an test\n";
    int i = 100;
    while(i){
    log(name, sizeof("log1.txt"), message, sizeof("this is a test"));
    i--;
    }

}
*/

