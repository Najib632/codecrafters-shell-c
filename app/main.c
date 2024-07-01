#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
exit_status(const char *cmd)
{
	int i, number = 0;

	for(i = 0; cmd[i]; i++)
	{
		if(cmd[i] >= '0' && cmd[i] <= '9')
		{
			number = number * 10 + (cmd[i] - '0');
		}
	}
	return (number);
}

void
check_exit(const char *cmd)
{
	int code = 0;
	code = exit_status(cmd);
	exit(code);
}

void
check_echo(const char *cmd)
{
	fprintf(stdout, "%s\n", cmd + 5);
}

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
	int i, limit = sizeof(builtins) / sizeof(builtins[0]);

	while (cmdlet != NULL)
	{
		for (i = 0; i < limit; i++)
		{
			if (strcmp(builtins[i], cmdlet) == 0)
			{
				printf("%s is a shell builtin\n", cmdlet);
				break;
			}
		}
		if (i == limit)
			printf("%s: not found\n", cmdlet);

		cmdlet = strtok(NULL, delim);
	}
}

int
check_builtin(const char *cmd)
{
	if (!strncmp("exit", cmd, 4))
	{
		check_exit(cmd);
	}
	else if (!strncmp("echo", cmd, 4))
	{
		check_echo(cmd);
		return (1);
	}
  else if (!strncmp("type", cmd, 4))
  {
    check_type(cmd + 5);
    return (1);
  }
	return (0);
}

int
main(void)
{
	int status = 1;

	while (status)
	{
		char input[100];

		/* Uncomment this block to pass the first stage */
		printf("$ ");
		fflush(stdout);

		/* Wait for user input */
		if (fgets(input, 100, stdin) != NULL)
			input[strlen(input) - 1] = '\0';
		else
			status = 0;

		if (check_builtin(input))
			continue;
		fprintf(stderr, "%s: command not found\n", input);
	}
	return (0);
}
