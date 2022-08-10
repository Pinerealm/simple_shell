#include "simple_sh.h"

/**
 * main - main shell function
 *
 * @argc: number of arguments
 * @argv: array of arguments
 * @envp: array of environment variables
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv, char **envp)
{
	char input_str[BUFF_SIZE], *args[MAX_ARGS], *line;
	size_t len = 0;
	ssize_t read;

	(void) argc;
	(void) argv;

	while (1)
	{
		prompt();
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			continue;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}
		if (line[0] == '\n')
		{
			free(line);
			continue;
		}
		strcpy(input_str, line);
		parse_str(input_str, args);
		execute(args, envp);
		free(line);
	}
	return (0);
}

