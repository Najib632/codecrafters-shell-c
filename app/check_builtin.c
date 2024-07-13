#include "main.h"

int
inpath(char *dir, char *cmd)
{
	struct dirent **namelist;
	int n;

	n = scandir(dir, &namelist, NULL, alphasort);
	if (n == -1)
	{
		perror("scandir");
		exit(EXIT_FAILURE);
	}

	while (n--)
	{
		/* Compare */
		fprintf(stdout, "%s == %s ?: ", namelist[n]->d_name, cmd);
		if (strncmp(namelist[n]->d_name, cmd, strlen(cmd)) == 0)
		{
			fprintf(stderr, "%s\n", "YES");
			return (1);
		}
		else
		{
			fprintf(stderr, "%s\n", "NO");
			continue;
		}
	}
	return (0);
}

int
check_path(char *cmd)
{
	char *PATH = getenv("PATH");
	char *path;

	path = strtok(PATH, ":");
	while (path != NULL)
	{
		/* TODO search for program in path and simultaneously update path */
		/* If path found break the loop */
		if (inpath(path, cmd))
		{
			/* concatenate the directory and command */
			fprintf(stdout, "%s is %s\n", cmd, strcat(path, cmd));
			return (1);
		}
		path = strtok(NULL, ":");
	}

	return (0);
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
