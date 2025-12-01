#include "shell.h"

/**
 * parse_command - parses a command into arguments
 * @command: string to parse
 * @argv: array to store arguments
 */
void parse_command(char *command, char **argv)
{
	char *token;
	int i = 0;

	token = _strtok(command, " \t\n");
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

	if (_strcmp(argv[0], "cd") == 0)
		return (handle_cd(argv, status, name, count));

	if (handle_env_commands(argv, status))
		return (1);

	return (0);
}

/**
 * process_input - processes the input line
 * @line: input line
 * @status: pointer to status variable
 * @name: program name
 * @count: line count
 *
 * Return: -1 to exit, 0 otherwise
 */
int process_input(char *line, int *status, char *name, int count)
{
	char *argv[1024], *commands[1024];
	int operators[1024];
	int i, num_commands, builtin_ret, execute_next = 1;

	num_commands = split_commands(line, commands, operators);

	for (i = 0; i < num_commands; i++)
	{
		if (execute_next)
		{
			parse_command(commands[i], argv);
			if (argv[0])
			{
				builtin_ret = handle_builtins(argv, status, name, count);
				if (builtin_ret == -1)
					return (-1);
				else if (builtin_ret == 0)
					*status = execute_command(argv, name, count);
			}
		}

		if (operators[i] == OP_AND)
			execute_next = (*status == 0) ? 1 : 0;
		else if (operators[i] == OP_OR)
			execute_next = (*status != 0) ? 1 : 0;
		else if (operators[i] == OP_SEMICOLON)
			execute_next = 1;
	}
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
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int count = 0, status = 0;

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

		if (process_input(line, &status, av[0], count) == -1)
			break;
	}
	free(line);
	free_env();
	return (status);
}
