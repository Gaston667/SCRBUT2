#include "helpers.h"

static char buffer[16 MB] = {0};

int main(int argc, char **argv)
{
	buffer[10] = 12;
	buffer[5000] = 45;
	randomize(buffer, 16 MB);
	return interlude();
}
