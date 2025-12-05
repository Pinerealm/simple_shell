#include "shell.h"

/**
 * extract_quoted_value - extracts a quoted value
 * @val_start: start of value (with quote)
 * @argv: argument vector
 * @i: current index
 * @value_buffer: buffer to store value
 *
 * Return: new index
 */
int extract_quoted_value(char *val_start, char **argv, int i,
		char *value_buffer)
{
	int vlen, m;
	char *real_val = val_start + 1;

	_strcpy(value_buffer, real_val);
	vlen = _strlen(value_buffer);
	if (vlen > 0 && value_buffer[vlen - 1] == '\'')
	{
		value_buffer[vlen - 1] = '\0';
		return (i);
	}

	for (m = i + 1; argv[m]; m++)
	{
		_strcat(value_buffer, " ");
		_strcat(value_buffer, argv[m]);
		vlen = _strlen(value_buffer);
		if (vlen > 0 && value_buffer[vlen - 1] == '\'')
		{
			value_buffer[vlen - 1] = '\0';
			return (m);
		}
	}
	return (i);
}

/**
 * extract_alias_value - extracts the value for an alias assignment
 * @arg: the argument string (name=value)
 * @val_start: pointer to the start of value in arg
 * @argv: argument vector (for lookahead)
 * @i: current index in argv
 * @buffer: buffer to store the name
 * @aliases: pointer to aliases list
 *
 * Return: new index in argv
 */
int extract_alias_value(char *arg, char *val_start, char **argv, int i,
		char *buffer, alias_t **aliases)
{
	int name_len = val_start - arg - 1;
	int k;
	char value_buffer[1024];

	for (k = 0; k < name_len; k++)
		buffer[k] = arg[k];
	buffer[k] = '\0';

	if (val_start[0] == '\'')
	{
		i = extract_quoted_value(val_start, argv, i, value_buffer);
		set_alias(buffer, value_buffer, aliases);
	}
	else
		set_alias(buffer, val_start, aliases);
	return (i);
}

/**
 * process_alias_arg - processes a single alias argument
 * @arg: argument string
 * @argv: argument vector
 * @i: current index
 * @aliases: pointer to aliases list
 * @status: pointer to status variable
 *
 * Return: new index
 */
int process_alias_arg(char *arg, char **argv, int i, alias_t **aliases,
		int *status)
{
	char *val_start = NULL;
	char buffer[1024];
	int j;

	for (j = 0; arg[j]; j++)
	{
		if (arg[j] == '=')
		{
			val_start = &arg[j + 1];
			break;
		}
	}

	if (val_start)
		return (extract_alias_value(arg, val_start, argv, i, buffer, aliases));

	if (print_alias(arg, *aliases) != 0)
	{
		_eputs("alias: ");
		_eputs(arg);
		_eputs(" not found\n");
		*status = 1;
	}
	return (i);
}

/**
 * handle_alias - handles the alias built-in
 * @argv: argument vector
 * @status: pointer to status variable
 * @name: program name
 * @count: line count
 * @aliases: pointer to aliases list
 *
 * Return: 1
 */
int handle_alias(char **argv, int *status, char *name, int count,
		alias_t **aliases)
{
	int i;

	(void)name;
	(void)count;

	if (!argv[1])
	{
		print_all_aliases(*aliases);
		*status = 0;
		return (1);
	}

	for (i = 1; argv[i]; i++)
	{
		i = process_alias_arg(argv[i], argv, i, aliases, status);
	}
	if (*status != 1)
		*status = 0;
	return (1);
}
