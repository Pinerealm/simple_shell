#include "shell.h"

/**
 * _atoi - converts a string to an integer
 * @s: string to convert
 * Return: the integer value of the converted string, or -1 if invalid
 */
int _atoi(char *s)
{
	int i = 0;
	unsigned long int n = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i]; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			n = n * 10 + (s[i] - '0');
			if (n > 2147483647)
				return (-1);
		}
		else
			return (-1);
	}
	return ((int)n);
}
