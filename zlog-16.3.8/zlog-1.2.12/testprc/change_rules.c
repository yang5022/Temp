#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "zlog.h"

void * work(void *ptr)
{
	int zc;
	sleep(5);
	char *str = (char *)ptr;
	zc = zlog_change_rule(str,"=info");
	
	if(zc){ 
		printf("change rule fail\n");
		zlog_fini();
		return (void *)-1;
	}

	return (void *)0;
}

int main(int argc, char** argv)
{
	int rc = 0;
	int j = 100;

    	rc = zlog_init("change_rule.conf");
    	if (rc){
    		printf("init failed\n");
        	return 2;
    	}

	zlog_category_t *zc;
	zc = zlog_get_category("yang");

	pthread_t  tid;
	pthread_create(&tid, NULL, work, (void*)("yang"));
	
	while(j-- > 0) {
		zlog_debug(zc, "debuglog");
		zlog_info(zc, "infolog");
		zlog_error(zc, "errorlog");
		sleep(1);
	}

	pthread_join(tid, NULL);
	zlog_fini();
	
	return 0;
}
