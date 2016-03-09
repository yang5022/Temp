#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "zlog.h"

int main(int argc, char** argv)
{
    int rc = 0;
    int j = 30;
    rc = zlog_init("dog.conf");
    if (rc){
    	printf("init failed\n");
        return 2;
    }
	zlog_category_t *zc;
	zc = zlog_get_category("cat");
	//vc = zlog_get_category("hat");
	
	while(j-- > 0) {
		zlog_debug(zc, " loglog");
		//zlog_error(vc, "logpress");
		sleep(1);	
	}

	zlog_fini();
	
	return 0;
}
