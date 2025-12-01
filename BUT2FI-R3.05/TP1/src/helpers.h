#ifndef _HELPERS_H
#define _HELPERS_H
#include <stdlib.h>

#define KB * 1024
#define MB * 1024 * 1024

void randomize(char *buf, size_t n);
void clean(size_t n);
void dirty(size_t n);
int interlude(void);

#endif
