#include "main.h"

int
main(void)
{
	while (1)
	{
		char input[100];

		/* Uncomment this block to pass the first stage */
		printf("$ ");
		fflush(stdout);

		/* Wait for user input */
		if (fgets(input, 100, stdin) != NULL)
			input[strlen(input) - 1] = '\0';
		else
			break;

		if (check_cmd(input) == 0)
			fprintf(stderr, "%s: command not found\n", input);
		else
			continue;
	}
	return (0);
}
