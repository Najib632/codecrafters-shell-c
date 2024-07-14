#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

typedef struct cmd_entry_s
{
	char *name;
	void (*cmd_func)(const char *);
} cmd_entry_t;

int check_path(char *cmdlet);
int check_builtin(char *cmdlet);
int check_cmd(const char *cmd);
int exit_status(const char *cmd);
void check_exit(const char *cmd);
void check_echo(const char *cmd);
void check_type(const char *cmd);

char *safe_strcat(char *, const char *);
