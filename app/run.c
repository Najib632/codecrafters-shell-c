#include "main.h"

/**
 * run - executes program
 * Description: Searches path for program and executes it
 * @cmd: the complete line of command
 *
 * Return: 0 (SUCCESS), 1 (FAILURE)
 **/
int
run(const char *cmd)
{
	char **cmdtok = _strtok((char *)cmd, " ");
	/* char *cmd_only = (char *)extract_cmd(cmd); */
	char *path = NULL;
	pid_t child_pid;
	int status;

	if (check_path(cmdtok[0], &path) == 0)
	{
		free_tok(cmdtok);
		return (1);
	}

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("fork");
		free(path);
		free_tok(cmdtok);
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		if (execve(path, cmdtok, NULL) < 0)
		{
			free(path);
			free_tok(cmdtok);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
		free(path);
		free_tok(cmdtok);
		return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
	}

	return (1);
}
