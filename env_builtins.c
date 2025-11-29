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

	if (environ)
	{
		for (i = 0; environ[i]; i++)
		{
			if (_strncmp(environ[i], name, _strlen(name)) == 0 &&
				environ[i][_strlen(name)] == '=')
			{
				free(environ[i]);
				environ[i] = new_str;
				return (0);
			}
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
	free(environ);
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

	if (!name || !environ)
		return (-1);

	len = _strlen(name);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			free(environ[i]);
			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];
			return (0);
		}
	}
	return (0);
}

/**
 * init_env - initializes the environment
 * @env: system environment
 */
void init_env(char **env)
{
	char **new_env;
	int i, count = 0;

	while (env[count])
		count++;

	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return;

	for (i = 0; i < count; i++)
		new_env[i] = _strdup(env[i]);
	new_env[i] = NULL;

	environ = new_env;
}

/**
 * free_env - frees the environment
 */
void free_env(void)
{
	int i;

	if (!environ)
		return;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}
