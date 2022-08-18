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
 * trim - removes leading and trailing whitespace
 * @str: string to be trimmed
 *
 * Return: void
 */
void trim(char *str)
{
	int i, j;

	for (i = 0; str[i] == ' ' || str[i] == '\t'; i++)
		;
	for (j = 0; str[j] != '\0'; j++)
		str[j] = str[j + i];
	str[j] = '\0';

	for (j = j - 1; j >= 0 && (str[j] == ' ' || str[j] == '\t'); j--)
		str[j] = '\0';
}
