#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "zlog.h"

//#define FIFONAME  "/usr/bin/cronolog"
//#define FIFONAME "./fifoswp"
#define FIFONAME "/home/iotek/fifoswp"

void readfifo(){
	int fd;
	char buf[24];
	int cnt;

	fd=open(FIFONAME,O_RDONLY);
	do{
		cnt=read(fd,buf,sizeof(buf));
		if(cnt==0){
			printf("write close!\n");
			break;
		}else if(cnt==-1){
			if(errno==EINTR){
				continue;
			}else{
				break;
			}
		}else{
			printf("read fifo:%s\n",buf);
		}
	}while(strcmp(buf,"exit")!=0);
	close(fd);
}
int main(int argc,char **argv)
{
	 int rc = 0;
    	 int j = 30;

	 remove(FIFONAME);
	 mkfifo(FIFONAME,0600);

    	 rc = zlog_init("pipe.conf");
         if (rc){
    	 	printf("init failed\n");
         	return 2;
    	 }
	zlog_category_t *zc;
	zc = zlog_get_category("pipe");

	while(j-- > 0) {
		zlog_debug(zc, "loglog");	
	}

	//readfifo();

	zlog_fini();

	return 0;
}

