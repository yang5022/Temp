#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "zlog.h"

static long loop_count;

/*struct prethd{
	int press_i;
	int thread_j;
}pre_thd;*/

void * work(void *ptr)
{
	long j = loop_count;
	char category[20];
	sprintf(category, "cat%ld", (long)ptr);
	zlog_category_t *zc;

	zc = zlog_get_category(category);
	
	while(j-- > 0) {
		zlog_debug(zc, " %s loglog", category);
		zlog_error(zc, "%s logpress", category);
	}
	return 0;
}


int test(long process_count, long thread_count)
{
	long i;
	pid_t pid;
	long j; 

	for (i = 0; i < process_count; i++) {
		pid = fork();
		if (pid < 0) {
			printf("fork fail\n");
		} else if(pid == 0) {
			pthread_t  tid[thread_count];

			for (j = 0; j < thread_count; j++) { 
				pthread_create(&(tid[j]), NULL, work, (void*)j);
			}
			for (j = 0; j < thread_count; j++) { 
				pthread_join(tid[j], NULL);
			}
			return 0;
		}
	}

	for (i = 0; i < process_count; i++) {
		pid = wait(NULL);
	}

	return 0;
}


int main(int argc, char** argv)
{
	int rc = 0;
	if (argc != 4) {
		fprintf(stderr, "test noprocess nothreads noloop\n");
		exit(1);
	}
	
    rc = zlog_init("zlog_test_press.conf");
    if (rc){
    	printf("init failed\n");
        return 2;
    }

	loop_count = atol(argv[3]);
	test(atol(argv[1]), atol(argv[2]));

	zlog_fini();
	
	return 0;
}
