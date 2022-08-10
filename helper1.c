#include "simple_sh.h"

/**
 * prompt - prints the prompt
 *
 * Return: void
 */
void prompt(void)
{
	printf("simple_sh:$ ");
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
 * @input_str: input string
 * @args: array of parsed arguments
 *
 * Return: void
 */
void parse_str(char *input_str, char **args)
{
	char *arg;
	int i = 0;

	arg = strtok(input_str, " \n");
	while (arg != NULL)
	{
		args[i++] = arg;
		arg = strtok(NULL, " \n");
	}
}

/**
 * execute - executes a command
 * @args: the line to be executed
 * @envp: the environment variables
 *
 * Return: void
 */
void execute(char **args, char **envp)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
		return;
	if (strcmp(args[0], "exit") == 0)
	{
		exit(0);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		print_env(envp);
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		char *path = args[1];

		if (path == NULL)
		{
			path = getenv("HOME");
		}
		chdir(path);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			execve(args[0], args, envp);
			perror("Error");
		}
		else
		{
			wait(&status);
		}
	}
}

