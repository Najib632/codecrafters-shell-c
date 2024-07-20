#include "main.h"

/**
 * check_type - Checks the type of each command in a string
 * Description: Determines if each command is a builtin, in PATH, or not found
 * @cmd: The string containing commands to check
 *
 * Return: Nothing
 **/
void
check_type(const char *cmd)
{
	char *cmd_copy = strdup(cmd + 5);
	const char *delim = " ";
	char *saveptr;
	char *cmdlet = strtok_r(cmd_copy, delim, &saveptr);
	char *path = NULL;

	/* TODO create a pointer to str that will store path */
	if (cmdlet == NULL)
	{
		exit(EXIT_SUCCESS);
	}
	while (cmdlet != NULL)
	{
		if (check_builtin(cmdlet) == 1)
		{
			fprintf(stdout, "%s is a shell builtin\n", cmdlet);
		}
		else if (check_path(cmdlet, &path) == 1)
		{
			fprintf(stdout, "%s is %s\n", cmdlet, path);
		}
		else
		{
			fprintf(stdout, "%s: not found\n", cmdlet);
		}
		cmdlet = strtok_r(NULL, delim, &saveptr);
	}
	free(cmdlet);
	free(cmd_copy);
	free(path);
}

/**
 * check_builtin - Checks if a command is a shell builtin
 * Description: Compares the given command against a list of known builtins
 * @cmdlet: The command to check
 *
 * Return: 1 if the command is a builtin, 0 otherwise
 **/
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

/**
 * check_path - Searches for a command in the PATH
 * Description: Looks for the given command in directories specified by PATH
 * @cmdlet: The command to search for
 * @dispth: Pointer to store the full path if found
 *
 * Return: 1 if command is found, 0 otherwise
 **/
int
check_path(char *cmdlet, char **dispth)
{
	char *PATH = NULL;
	char *PTHCPY = NULL;
	char *dir = NULL;
	char *full_path;
	char *saveptr = NULL;
	char *inpath = "/";
	char *delim = ":";

	PATH = getenv("PATH");
	if (dispth != NULL && PATH == NULL)
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
			*dispth = strdup(full_path);
			free(full_path);
			free(PTHCPY);
			return (1);
		}
		free(full_path);
		dir = strtok_r(NULL, delim, &saveptr);
	}
	free(dir);
	free(PTHCPY);
	return (0);
}

/**
 * safe_strcat - Safely concatenates two strings
 * Description: Allocates new memory if needed to concatenate strings
 * @dest: The destination string
 * @src: The source string to append
 *
 * Return: A pointer to the resulting string, or NULL on failure
 **/
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
