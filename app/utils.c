#include "main.h"

/**
 * _strlen - my own strlen function
 * @str: buffer
 *
 * Return: char length
 **/
size_t _strlen(char *str)
{
	size_t i;

	for (i = 0; str[i]; i++)
		;
	return (i);
}

/**
 * _strcspn - get length of a prefix substring
 * @s: string to scan for reject
 * @reject: char being scanned for in s
 *
 * Return: number of bytes in the initial segment of s
 *         which are not in the string reject.
 **/
size_t _strcspn(const char *s, const char *reject)
{
	size_t i, j;

	for (i = 0; s[i]; i++)
	{
		for (j = 0; reject[j]; j++)
		{
			if (s[i] == reject[j])
				return (i);
		}
	}
	return (i);
}

/**
 * _strchr - Locates first occurrence of the character c in the string s
 * @s: delimeter string
 * @c: character
 *
 * Return: Pointer to the matched character, NULL if the character is not found
 **/
char *_strchr(const char *s, int c)
{
	while (*s != '\0' && *s != c)
		s++;
	return (*s == (char)c ? (char *)s : NULL);
}

/**
 * extract_cmd - finds main command name
 * Description: extracts a command from a complete command line
 * @cmd: complete command line
 *
 * Return: command name, NULL otherwise
 **/
const char
*extract_cmd(const char *cmd)
{
	int i;
	char *extract;

	if (cmd == NULL)
		return (NULL);

	for (i = 0; cmd[i] != ' ' && cmd[i] != '\0'; i++)
	;

	extract = malloc((sizeof(char) * i) + 1);
	if (extract == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	for (i = 0; cmd[i] != ' ' && cmd[i + 1] == '\0'; i++)
	{
		extract[i] = cmd[i];
	}
	extract[i + 1] = '\0';

	return (extract);
}
