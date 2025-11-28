#include "shell.h"

/**
 * is_delim - checks if character is a delimiter
 * @c: character to check
 * @delim: string of delimiters
 *
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * _strtok - splits a string into words
 * @str: string to split
 * @delim: delimiters
 *
 * Return: pointer to next token or NULL
 */
char *_strtok(char *str, char *delim)
{
	static char *backup_string;
	char *token;

	if (!str)
		str = backup_string;
	if (!str)
		return (NULL);

	while (*str && is_delim(*str, delim))
		str++;
	if (*str == '\0')
	{
		backup_string = NULL;
		return (NULL);
	}

	token = str;
	while (*str && !is_delim(*str, delim))
		str++;

	if (*str)
	{
		*str = '\0';
		backup_string = str + 1;
	}
	else
		backup_string = NULL;

	return (token);
}
