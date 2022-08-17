#include "simple_sh.h"

/**
 * _strcpy - copies a string
 *
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to the destination string
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * get_input - gets the input from the command line
 *
 * @input_line: array to be filled with the input
 * @argv: command line arguments
 *
 * Return: no of characters read
 */
ssize_t get_input(char *input_line, char **argv)
{
	ssize_t nread;

	nread = read(STDIN_FILENO, input_line, MAX_INPUT);
		if (nread == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	input_line[nread] = '\0';
	return (nread);
}
