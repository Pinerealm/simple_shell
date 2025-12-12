#include "shell.h"

/**
 * print_env - prints the environment variables
 */
void print_env(void)
{
	int i = 0;

	if (!environ)
		return;

	while (environ[i])
	{
		_puts(environ[i]);
		_puts("\n");
		i++;
	}
}

/**
 * handle_setenv - handles setenv command
 * @argv: argument vector
 * @status: pointer to status variable
 *
 * Return: 1
 */
int handle_setenv(char **argv, int *status)
{
	if (argv[1] && argv[2])
	{
		if (_setenv(argv[1], argv[2]) == -1)
		{
			_eputs("Error: setenv failed\n");
			*status = 1;
		}
		else
			*status = 0;
	}
	else
	{
		_eputs("Usage: setenv VARIABLE VALUE\n");
		*status = 1;
	}
	return (1);
}

/**
 * handle_unsetenv - handles unsetenv command
 * @argv: argument vector
 * @status: pointer to status variable
 *
 * Return: 1
 */
int handle_unsetenv(char **argv, int *status)
{
	if (argv[1])
	{
		if (_unsetenv(argv[1]) == -1)
		{
			_eputs("Error: unsetenv failed\n");
			*status = 1;
		}
		else
			*status = 0;
	}
	else
	{
		_eputs("Usage: unsetenv VARIABLE\n");
		*status = 1;
	}
	return (1);
}

/**
 * handle_env_commands - handles env, setenv, and unsetenv
 * @argv: argument vector
 * @status: pointer to status variable
 *
 * Return: 1 if handled, 0 otherwise
 */
int handle_env_commands(char **argv, int *status)
{
	if (_strcmp(argv[0], "env") == 0)
	{
		print_env();
		*status = 0;
		return (1);
	}
	if (_strcmp(argv[0], "setenv") == 0)
		return (handle_setenv(argv, status));
	if (_strcmp(argv[0], "unsetenv") == 0)
		return (handle_unsetenv(argv, status));
	return (0);
}

/**
 * handle_builtins - handles built-in commands
 * @argv: argument vector
 * @status: pointer to status variable
 * @name: program name
 * @count: line count
 * @aliases: pointer to aliases list
 *
 * Return: 1 if built-in executed, 0 otherwise
 */
int handle_builtins(char **argv, int *status, char *name, int count,
		alias_t **aliases)
{
	if (_strcmp(argv[0], "exit") == 0)
		return (handle_exit(argv, status, name, count));

	if (_strcmp(argv[0], "cd") == 0)
		return (handle_cd(argv, status, name, count));

	if (_strcmp(argv[0], "alias") == 0)
		return (handle_alias(argv, status, name, count, aliases));

	if (handle_env_commands(argv, status))
		return (1);

	return (0);
}
