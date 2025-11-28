#include "shell.h"

/**
 * print_env - prints the environment variables
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		_puts(environ[i]);
		_puts("\n");
		i++;
	}
}
