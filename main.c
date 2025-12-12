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

/**
 * process_single_command - processes a single command
 * @command: command string
 * @status: pointer to status variable
 * @name: program name
 * @count: line count
 * @aliases: pointer to aliases list
 *
 * Return: -1 to exit, 0 otherwise
 */
int process_single_command(char *command, int *status, char *name, int count,
		alias_t **aliases)
{
	char *argv[1024], *alias_copies[20], *new_alias;
	char *var_copies[1024];
	int builtin_ret, alias_count = 0, i, var_count = 0;

	parse_command(command, argv);
	if (argv[0])
	{
		replace_variables(argv, *status, var_copies, &var_count);
		while (alias_count < 20)
		{
			new_alias = check_alias(argv, *aliases);
			if (!new_alias)
				break;
			alias_copies[alias_count++] = new_alias;
		}

		builtin_ret = handle_builtins(argv, status, name, count, aliases);
		if (builtin_ret == -1)
		{
			for (i = 0; i < alias_count; i++)
				free(alias_copies[i]);
			for (i = 0; i < var_count; i++)
				free(var_copies[i]);
			return (-1);
		}
		else if (builtin_ret == 0)
			*status = execute_command(argv, name, count);

		for (i = 0; i < alias_count; i++)
			free(alias_copies[i]);
		for (i = 0; i < var_count; i++)
			free(var_copies[i]);
	}
	return (0);
}

/**
 * process_input - processes the input line
 * @line: input line
 * @status: pointer to status variable
 * @name: program name
 * @count: line count
 * @aliases: pointer to aliases list
 *
 * Return: -1 to exit, 0 otherwise
 */
int process_input(char *line, int *status, char *name, int count,
		alias_t **aliases)
{
	char *commands[1024];
	int operators[1024];
	int i, num_commands, execute_next = 1;

	num_commands = split_commands(line, commands, operators);

	for (i = 0; i < num_commands; i++)
	{
		if (execute_next)
		{
			if (process_single_command(commands[i], status, name, count, aliases) == -1)
				return (-1);
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
	alias_t *aliases = NULL;

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
			free_aliases(aliases);
			exit(status);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		remove_comments(line);

		if (process_input(line, &status, av[0], count, &aliases) == -1)
			break;
	}
	free(line);
	free_env();
	free_aliases(aliases);
	return (status);
}
