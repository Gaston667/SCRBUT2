#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "helpers.h"

#include <stdlib.h>

void randomize(char *buf, size_t n)
{
	assert(buf);
	memset(buf, rand() & 0xff, n);
}

void clean(size_t b)
{
	for (; b > 0; b -= 1 KB)
		calloc(1 KB, sizeof(char));
}

void dirty(size_t b)
{
	for (; b > 0; b -= 1 KB)
		randomize(calloc(1 KB, sizeof(char)), 1 KB);
}

int interlude(void)
{
	pid_t pid = getpid();
	printf("pid %i\n", (int)pid);
	printf("------------------------------------------\n"
	       "go check /proc/%i/smaps; I'll wait...\n"
	       "press <Enter> when you're done\n", pid);
	fgetc(stdin);
	return 0;
}
