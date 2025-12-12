#include "shell.h"

/**
 * _itoa - converts integer to string
 * @n: integer to convert
 *
 * Return: pointer to new string
 */
char *_itoa(int n)
{
	char buffer[20], *s;
	int i = 0, j, is_negative = 0;
	unsigned int num;

	if (n == 0)
		return (_strdup("0"));

	if (n < 0)
	{
		num = -n;
		is_negative = 1;
	}
	else
		num = n;

	while (num > 0)
	{
		buffer[i++] = (num % 10) + '0';
		num /= 10;
	}

	if (is_negative)
		buffer[i++] = '-';

	buffer[i] = '\0';

	s = malloc(i + 1);
	if (!s)
		return (NULL);
	for (j = 0; j < i; j++)
		s[j] = buffer[i - j - 1];
	s[i] = '\0';
	return (s);
}

/**
 * replace_variables - replaces variables in argv
 * @argv: argument vector
 * @status: last exit status
 * @var_copies: array to store allocated strings
 * @var_count: pointer to count of allocated strings
 */
void replace_variables(char **argv, int status, char **var_copies,
		int *var_count)
{
	int i;
	char *val;

	for (i = 0; argv[i]; i++)
	{
		if (argv[i][0] != '$' || !argv[i][1])
			continue;

		val = NULL;
		if (_strcmp(argv[i], "$?") == 0)
		{
			val = _itoa(status);
		}
		else if (_strcmp(argv[i], "$$") == 0)
		{
			val = _itoa(getpid());
		}
		else
		{
			char *env_val = _getenv(argv[i] + 1);

			if (env_val)
				val = _strdup(env_val);
			else
				val = _strdup("");
		}

		if (val)
		{
			argv[i] = val;
			if (*var_count < 1024)
				var_copies[(*var_count)++] = val;
			else
				free(val);
		}
	}
}
