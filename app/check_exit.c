#include "main.h"

/**
 * check_exit - Handles the exit command
 * Description: Parses the exit status and terminates the program
 * @cmd: The full exit command string
 *
 * Return: Does not return, terminates the program
 **/
void
check_exit(const char *cmd)
{
	int code = 0;

	code = exit_status(cmd);
	exit(code);
}
