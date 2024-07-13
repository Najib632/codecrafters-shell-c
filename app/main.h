#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

int inpath(char *dir, char *cmd);
int check_path(char *cmd);
int check_builtin(const char *cmd);
int exit_status(const char *cmd);
void check_exit(const char *cmd);
void check_echo(const char *cmd);
void check_type(const char *cmd);
