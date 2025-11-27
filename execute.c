#include "shell.h"

/**
 * execute_command - forks and executes a command
 * @argv: argument vector
 * @name: program name for errors
 * @count: line counter
 */
void execute_command(char **argv, char *name, int count)
{
	pid_t child_pid;
	int status;
	char *command_path;

	command_path = get_path(argv[0]);
	if (command_path == NULL)
	{
		print_error(name, argv[0], count);
		return;
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		free(command_path);
		return;
	}
	if (child_pid == 0)
	{
		if (execve(command_path, argv, environ) == -1)
		{
			free(command_path);
			_exit(127);
		}
	}
	else
	{
		wait(&status);
		free(command_path);
	}
}
