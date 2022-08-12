#include "simple_sh.h"

/**
 * destroy_args - sets all the arguments to NULL
 * @args: array of arguments
 *
 * Return: void
 */
void destroy_args(char **args)
{
	int i;

	for (i = 0; args[i] != NULL; i++)
		args[i] = NULL;
}
