#include "main.h"

int
exit_status(const char *cmd)
{
	int i, number = 0;

	for (i = 0; cmd[i]; i++)
	{
		if (cmd[i] >= '0' && cmd[i] <= '9')
		{
			number = number * 10 + (cmd[i] - '0');
		}
	}
	return (number);
}
