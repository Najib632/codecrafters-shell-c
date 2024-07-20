#include "main.h"

/**
 * check_echo - Implements the echo command
 * Description: Prints the arguments of the echo command
 * @cmd: The full echo command string
 *
 * Return: Nothing
 **/
void
check_echo(const char *cmd)
{
	fprintf(stdout, "%s\n", cmd + 5);
}
