#include "main.h"

void
check_exit(const char *cmd)
{
	int code = 0;

	code = exit_status(cmd);
	exit(code);
}
