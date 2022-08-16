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
	char *input_line_arr[MAX_LINES], input[MAX_INPUT] = "\0";
	char *args[MAX_ARGS], *line = NULL, input_line[120] = "\0";
	size_t len = 0, i, j, line_count = 0;
	ssize_t g_read, r_read;
	int status;

	(void) argc;
	init_arr(input_line_arr, MAX_LINES);
	init_arr(args, MAX_ARGS);
	while (TRUE)
	{
		is_interactive(&status); /* check if the shell is interactive */

		if (status == 0)
		{
			/* count the number of new lines (\n) in the input */
			r_read = read(STDIN_FILENO, input, MAX_INPUT);
			if (r_read == -1)
			{
				perror(argv[0]);
				return (EXIT_FAILURE);
			}
			input[r_read] = '\0';
			for (i = 0, j = 0; input[i] != '\0'; i++)
			{
				if (input[i] == '\n')
				{
					input_line[j] = '\0';
					j = 0;
					input_line_arr[line_count] = _strdup(input_line);
					line_count++;
				}
				else
					input_line[j++] = input[i];
			}
			for (i = 0; input_line_arr[i] != NULL; i++)
			{
				parse_str(input_line_arr[i], args);
				execute(args, line, argv, input_line_arr);
			}
			free_line_arr(input_line_arr);
			break;
		}
		else
		{
			g_read = getline(&line, &len, stdin);
			if (g_read == -1)
			{
				free(line);
				continue;
			}
			if (line[0] == '\n')
				continue;

			_strcpy(input, line);
			parse_str(input, args);
			execute(args, line, argv, input_line_arr);
		}
	}
	return (0);
}
