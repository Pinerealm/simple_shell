#include "shell.h"

/**
 * _getenv - gets environment variable
 * @name: name of variable
 * Return: value of variable or NULL
 */
char *_getenv(const char *name)
{
	int i = 0, len;

	if (!name || !environ)
		return (NULL);

	len = _strlen((char *)name);

	while (environ[i])
	{
		if (_strncmp(environ[i], (char *)name, len) == 0 && environ[i][len] == '=')
		{
			return (environ[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

/**
 * build_full_path - builds full path for command
 * @dir: directory
 * @cmd: command
 *
 * Return: full path
 */
char *build_full_path(char *dir, char *cmd)
{
	char *full_path;
	int len;

	len = _strlen(dir) + _strlen(cmd) + 2;
	full_path = malloc(len);
	if (full_path == NULL)
		return (NULL);

	_strcpy(full_path, dir);
	_strcat(full_path, "/");
	_strcat(full_path, cmd);
	return (full_path);
}

/**
 * get_path - finds the full path of a command
 * @cmd: command to find
 * Return: full path or NULL
 */
char *get_path(char *cmd)
{
	char *path_env, *path_copy, *dir, *full_path;
	struct stat st;
	int i;

	if (cmd == NULL)
		return (NULL);
	for (i = 0; cmd[i]; i++)
	{
		if (cmd[i] == '/')
		{
			if (stat(cmd, &st) == 0)
				return (_strdup(cmd));
			return (NULL);
		}
	}
	path_env = _getenv("PATH");
	if (!path_env)
		return (NULL);
	path_copy = _strdup(path_env);
	if (!path_copy)
		return (NULL);
	dir = _strtok(path_copy, ":");
	while (dir)
	{
		full_path = build_full_path(dir, cmd);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = _strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
