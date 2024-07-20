#include "main.h"

/**
 * check_cmd - Checks and executes a command
 * Description: Determines the type of command and executes it accordingly
 * @cmd: The command string to check and execute
 *
 * Return: 1 if the command was executed, 0 if not found
 **/
int
check_cmd(const char *cmd)
{
	const cmd_entry_t cmd_table[] = {
		{"exit", check_exit},
		{"echo", check_echo},
		{"type", check_type},
		{NULL, NULL}
	};
	if (cmd == NULL)
	{
		exit(EXIT_SUCCESS);
	}
	for (int i = 0; cmd_table[i].name != NULL; i++)
	{
		if (strncmp(cmd_table[i].name, cmd, strlen(cmd_table[i].name)) == 0)
		{
			cmd_table[i].cmd_func(cmd);
			return (1);
		}
	}

	return (run(cmd) ? 0 : 1);
}
