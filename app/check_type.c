#include "main.h"

void
check_type(const char *cmd)
{
	char *cmd_copy = strdup(cmd + 5);
	const char *delim = " ";
	char *saveptr;
	char *cmdlet = strtok_r(cmd_copy, delim, &saveptr);

	if (cmdlet == NULL)
	{
		perror("strtok");
		exit(EXIT_FAILURE);
	}
	while (cmdlet != NULL)
	{
		if (check_builtin(cmdlet) == 1)
		{
			fprintf(stdout, "%s is a shell builtin\n", cmdlet);
		}
		else if (check_path(cmdlet) == 0)
		{
			fprintf(stdout, "%s: not found\n", cmdlet);
		}
		cmdlet = strtok_r(NULL, delim, &saveptr);
	}
	free(cmd_copy);
}

int
check_builtin(char *cmdlet)
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
	};
	int i, limit = sizeof(builtins) / sizeof(builtins[0]);

	for (i = 0; i < limit; i++)
	{
		if (strcmp(cmdlet, builtins[i]) == 0)
		{
			return (1);
		}
	}
	return (0);
}

int
check_path(char *cmdlet)
{
	char *PATH = NULL;
	char *PTHCPY = NULL;
	char *dir = NULL;
	char *full_path;
	char *saveptr = NULL;
	char *inpath = "/";
	char *delim = ":";

	PATH = getenv("PATH");
	if (PATH == NULL)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	PTHCPY = strdup(PATH);
	if (PTHCPY == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	dir = strtok_r(PTHCPY, delim, &saveptr);
	if (dir == NULL)
	{
		perror("check_path: strtok");
		exit(EXIT_FAILURE);
	}
	while (dir != NULL)
	{
		full_path = NULL;
		full_path = safe_strcat(full_path, dir);
		if (full_path == NULL)
		{
			perror("dir: strcat");
			free(PTHCPY);
			exit(EXIT_FAILURE);
		}
		full_path = safe_strcat(full_path, inpath);
		if (full_path == NULL)
		{
			perror("inpath: strcat");
			free(PTHCPY);
			exit(EXIT_FAILURE);
		}
		full_path = safe_strcat(full_path, cmdlet);
		if (full_path == NULL)
		{
			perror("cmdlet: strcat");
			free(PTHCPY);
			exit(EXIT_FAILURE);
		}
		if (access(full_path, X_OK) == 0)
		{
			fprintf(stdout, "%s is %s\n", cmdlet, full_path);
			return (1);
		}
		free(full_path);
		dir = strtok_r(NULL, delim, &saveptr);
	}
	free(dir);
	free(PTHCPY);
	return (0);
}

char
*safe_strcat(char *dest, const char *src)
{
	if (dest == NULL)
	{
		return (strdup(src));
	}

	size_t dest_len = strlen(dest);
	size_t src_len = strlen(src);
	size_t new_len = dest_len + src_len + 1;
	char *new_dest = realloc(dest, new_len);

	if (new_dest == NULL)
	{
		perror("realloc");
		return (NULL);
	}
	strcat(new_dest + dest_len, src);
	return (new_dest);
}
