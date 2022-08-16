#include "simple_sh.h"

/**
 * init_arr - initialize the array of arguments
 *
 * @array: array of arguments
 * @size: size of the array
 *
 * Return: void
 */
void init_arr(char **array, int size)
{
	int i;

	for (i = 0; i < size; i++)
		array[i] = NULL;
}

/**
 * _strncpy - copies, at most, n characters from a string
 *
 * @dest: destination string
 * @src: source string
 * @n: number of characters to copy
 *
 * Return: pointer to the destination string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for ( ; i < n; i++)
		dest[i] = '\0';
	return (dest);
}

/**
 * _getline - gets a line from stdin
 *
 * @line: pointer to the line to be filled
 * @len: pointer to the length of the line
 *
 * Return: pointer to the line on success, NULL on failure
 */
char *_getline(char **line, size_t *len)
{
	char *line_str = NULL, *prompt = "simple_sh:$ ";
	ssize_t read, p_len = 13;

	write(STDIN_FILENO, prompt, p_len);
	read = getline(line, len, stdin);
	if (read == -1 || *line[0] == '\n')
		return (line_str);

	line_str = malloc(sizeof(char) * read + 1);
	if (line_str == NULL)
		return (line_str);

	_strncpy(line_str, *line, read - 1);
	free(*line);
	return (line_str);
}

/**
 * _strdup - duplicates a string
 * @str: string to be duplicated
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(char *str)
{
	char *dup = NULL;
	int i, len = 0;

	if (str == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	_strncpy(dup, str, len);
	dup[len] = '\0';

	return (dup);
}

/**
 * free_line_arr - frees the array of arguments
 * @array: array of arguments
 *
 * Return: void
 */
void free_line_arr(char **array)
{
	int i;

	for (i = 0; array[i] != NULL; i++)
		free(array[i]);
}
