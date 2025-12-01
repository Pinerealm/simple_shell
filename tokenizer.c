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

/**
 * split_commands - splits line into commands based on separators
 * @line: input line
 * @commands: array to store commands
 * @operators: array to store operators
 *
 * Return: number of commands
 */
int split_commands(char *line, char **commands, int *operators)
{
	char *cursor = line;
	int i = 0, op;

	if (!line)
		return (0);

	commands[i] = cursor;
	while (*cursor)
	{
		if (*cursor == ';')
		{
			op = OP_SEMICOLON;
			*cursor = '\0';
			operators[i++] = op;
			cursor++;
			commands[i] = cursor;
		}
		else if (*cursor == '&' && *(cursor + 1) == '&')
		{
			op = OP_AND;
			*cursor = '\0';
			operators[i++] = op;
			cursor += 2;
			commands[i] = cursor;
		}
		else if (*cursor == '|' && *(cursor + 1) == '|')
		{
			op = OP_OR;
			*cursor = '\0';
			operators[i++] = op;
			cursor += 2;
			commands[i] = cursor;
		}
		else
			cursor++;
	}
	operators[i] = OP_NONE;
	return (i + 1);
}
