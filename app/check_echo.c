#include "main.h"

void
check_echo(const char *cmd)
{
	fprintf(stdout, "%s\n", cmd + 5);
}
