#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct cmd_entry_s
{
	char *name;
	void (*cmd_func)(const char *);
} cmd_entry_t;

int check_path(char *cmdlet, char **path);
int check_builtin(char *cmdlet);
int check_cmd(const char *cmd);
int exit_status(const char *cmd);
int run(const char *cmd);

void check_exit(const char *cmd);
void check_echo(const char *cmd);
void check_type(const char *cmd);

char *safe_strcat(char *, const char *);
const char *extract_cmd(const char *);
char **_strtok(char *str, const char *delim);
char *_strchr(const char *s, int c);
size_t _strlen(char *str);
size_t _strcspn(const char *s, const char *reject);
void free_tok(char **token);
