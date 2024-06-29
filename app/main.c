#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
exit_status(const char *cmd)
{
	char *code = (char *)cmd;
	char c; 
	int i, len, digit, number = 0;

	len = strlen(code);
	for(i = 0; i < len; i++) 
    {
		c = code[i]; 
		if(c >= '0' && c <= '9')
		{
			digit = c - '0'; 
			number = number * 10 + digit;
		}
    }
	return (number);
}

void
check_exit(const char *cmd)
{
	int code = 0;
	if (!strncmp("exit", cmd, 4)) {
		code = exit_status(cmd);
		exit(code);
	}
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

		check_exit(input);
		fprintf(stderr, "%s: command not found\n", input);
	}
	return (0);
}
