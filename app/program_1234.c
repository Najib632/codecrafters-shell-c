#include <stdlib.h>
#include <stdio.h>

/**
 * main - Entry point
 * Description: Prints a simple message using argv
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: Always 0
 **/
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <name>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "Hello %s! The secret code is 1234.\n", argv[1]);

	return (0);
}
