#include "main.h"

void
check_type(const char *cmd)
{
	const char *builtins[] = {
		".", ":", "[", "alias", "bg", "bind", "break", "builtin", "caller", "cd",
		"command", "compgen", "complete", "compopt", "continue", "declare", "dirs",
		"disown", "echo", "enable", "eval", "exec", "exit", "export", "false", "fc",
		"fg", "getopts", "hash", "help", "history", "jobs", "kill", "let", "local",
		"logout", "mapfile", "popd", "printf", "pushd", "pwd", "read", "readarray",
		"readonly", "return", "set", "shift", "shopt", "source", "suspend", "test",
		"times", "trap", "true", "type", "typeset", "ulimit", "umask", "unalias",
		"unset", "wait"
	}, *delim = " ", *cmdlet = strtok((char *)cmd, delim);
	int i, limit = sizeof(builtins) / sizeof(builtins[0]), status;

	while (cmdlet != NULL)
	{
		for (i = 0; i < limit; i++)
		{
			if (strcmp(builtins[i], cmdlet) == 0)
			{
				fprintf(stdout, "%s is a shell builtin\n", cmdlet);
				break;
			}
			status = check_path((char *)cmdlet);
			if (status == 1)
			{
				break;
			}
		}
		if (i == limit && !status)
			printf("%s: not found\n", cmdlet);

		cmdlet = strtok(NULL, delim);
	}
}
