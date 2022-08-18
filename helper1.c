#include "simple_sh.h"

/**
 * is_interactive - checks the shell mode
 * @status: shell status; 0 if interactive, 1 if not
 *
 * Return: void
 */
void is_interactive(int *status)
{
	if (isatty(STDIN_FILENO) == 1)
	{
		*status = 1;
		write(STDOUT_FILENO, "simple_sh:$ ", 13);
	}
	else
	{
		*status = 0;
	}
}

/**
 * print_env - prints the environment variables
 * @env: array of environment variables
 *
 * Return: void
 */
void print_env(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
		printf("%s\n", env[i]);
}

/**
 * parse_str - parses the input string
 *
 * @input: input string
 * @args: array of parsed arguments
 *
 * Return: void
 */
void parse_str(char *input, char **args)
{
	char *arg;
	int i = 0;

	if (args[0])
		init_arr(args, MAX_ARGS);
	trim(input);

	arg = strtok(input, " \n\t");
	while (arg != NULL && i < MAX_ARGS)
	{
		args[i++] = arg;
		arg = strtok(NULL, " \n\t");
	}
}

/**
 * handle_builtins - handles builtin commands
 * @args: array of parsed arguments
 *
 * Return: 0 on success, 1 on failure
 */
int handle_builtins(char **args)
{
	if (strcmp(args[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		print_env(__environ);
		return (0);
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		char *path = args[1];

		if (path == NULL)
		{
			path = getenv("HOME");
		}
		chdir(path);
		return (0);
	}
	else
	{
		return (1);
	}
}

/**
 * execute - executes a command
 *
 * @args: the parsed arguments
 * @argv: the command line arguments
 *
 * Return: void
 */
void execute(char **args, char **argv)
{
	pid_t child_pid;
	int status = 0;

	if (args[0] == NULL)
		return;
	if (handle_builtins(args) == 1)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			if (execve(args[0], args, __environ) == -1)
			{
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(&status);
	}
}
