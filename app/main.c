#include <stdio.h>
#include <string.h>

int
main(void) {
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

		fprintf(stderr, "%s: command not found\n", input);
	}
	return (0);
}
