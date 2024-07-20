#include "main.h"

#define IN      1
#define OUT     0

/**
 * free_tok - frees allocated memory to a 2D array grid
 * @token: pointer to 2D array to be freed
 *
 * Return: Nothing
 **/
void free_tok(char **token)
{
	int i;

	if (token == NULL)
		return;

	for (i = 0; token[i]; i++)
		free(token[i]);
	free(token);
}

/**
 * wcount - counts the number of words in a string
 * @str: string to count words in
 * @delim: delimeter
 *
 * Return: Number of words (SUCCESSFUL), 0 (FAILURE)
 **/
int wcount(char *str, const char *delim)
{
	int i, k, state, wordn;

	wordn = 0;
	state = OUT;
	for (i = 0; str[i]; i++)
	{
		for (k = 0; delim[k]; k++)
		{
			if (str[i] == delim[k])
			{
				if (state == IN)
				{
					state = OUT;
				}
			}
			else if (state == OUT)
			{
				state = IN;
				wordn += 1;
			}
		}
	}
	return (wordn);
}

/**
 * parser - writes the token
 * @token: string vector
 * @str: parsing string
 * @chrc: character count
 * @i: word end
 * @wrdc: token index
 *
 * Return: Nothing.
 **/
void parser(char **token, char *str, int chrc, int i, int wrdc)
{
	int k, m;

	for (k = 0, m = chrc; k <= chrc; k++, m--)
		if (k < chrc)
			token[wrdc][k] = str[(i + 1) - m];
		else
			token[wrdc][k] = '\0';
}

/**
 * _strtok - returns a pointer to an array of strings (words)
 * @str: string to be split in words
 * @delim: delimeter
 *
 * Return: pointer (SUCCESS), NULL (FAILURE)
**/
char **_strtok(char *str, const char *delim)
{
	char **token;
	int i, chrc = 0, wrdc;

	wrdc = wcount(str, delim);
	if (str == NULL || wrdc == 0)
		return (NULL);
	token = malloc((wrdc + 1) * sizeof(token));
	if (token == NULL)
		return (NULL);
	token[wrdc] = NULL;
	for (i = 0, wrdc = -1; str[i]; i++)
	{
		if (_strchr(delim, str[i]) == NULL)
		{
			chrc++;
			if (_strchr(delim, str[i + 1]) || str[i + 1] == '\0')
			{
				wrdc++;
				token[wrdc] = malloc((chrc + 1) * sizeof(char));
				if (token[wrdc] == NULL)
				{
					free_tok(token);
					return (NULL);
				}
				parser(token, str, chrc, i, wrdc);
				chrc = 0;
			}
		}
	}
	return (token);
}
