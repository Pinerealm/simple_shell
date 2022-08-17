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
	char input[MAX_INPUT] = "\0", input_line[120] = "\0", *args[MAX_ARGS];
	int i, j, status;
	ssize_t nread;

	(void) argc, (void) envp;
	init_arr(args, MAX_ARGS);
	while (TRUE)
	{
		is_interactive(&status); /* check if the shell is interactive */

		nread = get_input(input, argv);
		if (status == INTERACTIVE)
		{
			if (input[0] == '\n')
				continue;
			input[nread - 1] = '\0';
			parse_str(input, args);
			execute(args, argv);
			continue;
		}
		else
		{
			for (i = 0, j = 0; input[i] != '\0'; i++)
			{
				if (input[i] == '\n')
				{
					input_line[j] = '\0';
					j = 0;
					parse_str(input_line, args);
					execute(args, argv);
				}
				else
					input_line[j++] = input[i];
			}
			break;
		}
	}
	return (0);
}
