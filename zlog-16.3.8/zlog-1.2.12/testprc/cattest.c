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
    int j = 100;
    rc = zlog_init("cat.conf");
    if (rc){
    	printf("init failed\n");
        return 2;
    }
	zlog_category_t *zc;
	zc = zlog_get_category("cat");
	//zc = zlog_get_category("");
	
	while(j-- > 0) {
		zlog_debug(zc, " loglog");
		sleep(1);
		//zlog_error(zc, "logpress");	
	}

	zlog_fini();
	
	return 0;
}
