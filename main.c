#include "shell.h"

/**
 * parse_line - parses a line into arguments
 * @line: string to parse
 * @argv: array to store arguments
 */
void parse_line(char *line, char **argv)
{
	char *token;
	int i = 0;

	token = _strtok(line, " \t\n");
	while (token && i < 1023)
	{
		argv[i++] = token;
		token = _strtok(NULL, " \t\n");
	}
	argv[i] = NULL;
}

/**
 * handle_builtins - handles built-in commands
 * @argv: argument vector
 * @status: pointer to status variable
 * @name: program name
 * @count: line count
 *
 * Return: 1 if built-in executed, 0 otherwise
 */
int handle_builtins(char **argv, int *status, char *name, int count)
{
	if (_strcmp(argv[0], "exit") == 0)
		return (handle_exit(argv, status, name, count));

	if (handle_env_commands(argv, status))
		return (1);

	return (0);
}

/**
 * main - simple shell main loop
 * @ac: argument count
 * @av: argument vector
 * @env: environment vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL, *argv[1024];
	size_t len = 0;
	ssize_t nread;
	int count = 0, status = 0, builtin_ret;

	(void)ac;

	init_env(env);
	while (1)
	{
		count++;
		if (isatty(STDIN_FILENO))
			_puts("($) ");

		nread = _getline(&line, &len, STDIN_FILENO);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				_puts("\n");
			free(line);
			free_env();
			exit(status);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		parse_line(line, argv);

		if (argv[0])
		{
			builtin_ret = handle_builtins(argv, &status, av[0], count);
			if (builtin_ret == -1)
				break;
			else if (builtin_ret == 0)
				status = execute_command(argv, av[0], count);
		}
	}
	free(line);
	free_env();
	return (status);
}
