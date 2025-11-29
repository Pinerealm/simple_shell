#include "shell.h"

/**
 * _setenv - initializes or modifies an environment variable
 * @name: variable name
 * @value: variable value
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(char *name, char *value)
{
	char *new_str, **new_env;
	int i, len = 0;

	if (!name || !value)
		return (-1);
	new_str = malloc(_strlen(name) + _strlen(value) + 2);
	if (!new_str)
		return (-1);
	_strcpy(new_str, name);
	_strcat(new_str, "=");
	_strcat(new_str, value);
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], name, _strlen(name)) == 0 &&
		    environ[i][_strlen(name)] == '=')
		{
			environ[i] = new_str;
			return (0);
		}
	}
	len = i;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
	{
		free(new_str);
		return (-1);
	}
	for (i = 0; i < len; i++)
		new_env[i] = environ[i];
	new_env[i] = new_str;
	new_env[i + 1] = NULL;
	environ = new_env;
	return (0);
}

/**
 * _unsetenv - removes an environment variable
 * @name: variable name
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(char *name)
{
	int i, j, len;

	if (!name)
		return (-1);

	len = _strlen(name);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];
			return (0);
		}
	}
	return (0);
}
