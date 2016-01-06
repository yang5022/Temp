#include <stdio.h>

#include "debug.h"

int main(void){
	//int cnt;
	char *string = "ladfgaskgfdlk";

	debug_context_t* pd = debug_create_context("iotek");
	debug(pd,"string = %s",string);

	return 0;
}
