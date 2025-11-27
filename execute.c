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

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			print_error(name, argv[0], count);
			_exit(127);
		}
	}
	else
	{
		wait(&status);
	}
}
