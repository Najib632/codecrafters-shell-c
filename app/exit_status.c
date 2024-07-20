#include "main.h"

/**
 * exit_status - Extracts the exit status from a command string
 * Description: Parses the numeric exit status from the command string
 * @cmd: The command string containing the exit status
 *
 * Return: The parsed exit status as an integer
 **/
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
