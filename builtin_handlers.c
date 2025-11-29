#include "shell.h"

/**
 * handle_exit - handles the exit built-in
 * @argv: argument vector
 * @status: pointer to status variable
 * @name: program name
 * @count: line count
 *
 * Return: -1 to exit shell, 1 if error
 */
int handle_exit(char **argv, int *status, char *name, int count)
{
	int exit_val;

	if (argv[1])
	{
		exit_val = _atoi(argv[1]);
		if (exit_val == -1)
		{
			*status = 2;
			print_exit_error(name, count, argv[1]);
			return (1);
		}
		*status = exit_val;
	}
	return (-1);
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
