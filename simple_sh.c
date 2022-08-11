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
	char input_str[BUFF_SIZE], *args[MAX_ARGS], *line = NULL;
	size_t len = 0;
	ssize_t read;
	int status;

	(void) argc;
	init(&status); /* check if the shell is interactive */
	while (TRUE)
	{
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			prompt();
			continue;
		}
		if (line[0] == '\n')
		{
			prompt();
			continue;
		}

		strcpy(input_str, line);
		parse_str(input_str, args);
		execute(args, envp, line, argv);
		if (status == 0)
			break;
		prompt();
	}
	return (0);
}
