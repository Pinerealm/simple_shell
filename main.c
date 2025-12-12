#include "shell.h"

/**
 * handle_file_input - handles file input mode
 * @ac: argument count
 * @av: argument vector
 *
 * Return: file descriptor or -1 on error
 */
int handle_file_input(int ac, char **av)
{
	int fd = STDIN_FILENO;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			_eputs(av[0]);
			_eputs(": 0: Can't open ");
			_eputs(av[1]);
			_eputs("\n");
			exit(127);
		}
	}
	return (fd);
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
 * cleanup - frees memory and closes file descriptor
 * @line: input line
 * @aliases: aliases list
 * @fd: file descriptor
 */
void cleanup(char *line, alias_t *aliases, int fd)
{
	free(line);
	free_env();
	free_aliases(aliases);
	if (fd != STDIN_FILENO)
		close(fd);
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
	int count = 0, status = 0, fd;
	alias_t *aliases = NULL;

	fd = handle_file_input(ac, av);
	init_env(env);
	while (1)
	{
		count++;
		if (isatty(STDIN_FILENO) && ac == 1)
			_puts("($) ");

		nread = _getline(&line, &len, fd);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO) && ac == 1)
				_puts("\n");
			cleanup(line, aliases, fd);
			exit(status);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		remove_comments(line);

		if (process_input(line, &status, av[0], count, &aliases) == -1)
			break;
	}
	cleanup(line, aliases, fd);
	return (status);
}
