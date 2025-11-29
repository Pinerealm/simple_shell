#include "shell.h"

/**
 * handle_exit - handles the exit built-in
 * @argv: argument vector
 * @status: pointer to status variable
 * @name: program name
 * @count: line count
 *
 * Return: -1 to exit shell, 1 if error
 */
int handle_exit(char **argv, int *status, char *name, int count)
{
	int exit_val;

	if (argv[1])
	{
		exit_val = _atoi(argv[1]);
		if (exit_val == -1)
		{
			*status = 2;
			print_exit_error(name, count, argv[1]);
			return (1);
		}
		*status = exit_val;
	}
	return (-1);
}

/**
 * change_dir - changes directory and updates env
 * @dir: directory to change to
 * @old_pwd: old working directory
 *
 * Return: 0 on success, -1 on failure
 */
int change_dir(char *dir, char *old_pwd)
{
	char buffer[1024];

	if (chdir(dir) == -1)
		return (-1);
	_setenv("OLDPWD", old_pwd);
	if (getcwd(buffer, 1024))
		_setenv("PWD", buffer);
	return (0);
}

/**
 * handle_cd - changes the current directory
 * @argv: argument vector
 * @status: pointer to status variable
 * @name: program name
 * @count: line count
 *
 * Return: 1
 */
int handle_cd(char **argv, int *status, char *name, int count)
{
	char *dir, old_pwd[1024];

	if (!getcwd(old_pwd, 1024))
		old_pwd[0] = '\0';
	if (!argv[1])
	{
		dir = _getenv("HOME");
		if (!dir)
			return (1);
	}
	else if (_strcmp(argv[1], "-") == 0)
	{
		dir = _getenv("OLDPWD");
		if (!dir)
		{
			_puts(old_pwd), _puts("\n");
			*status = 0;
			return (1);
		}
		_puts(dir), _puts("\n");
	}
	else
		dir = argv[1];
	if (change_dir(dir, old_pwd) == -1)
	{
		print_cd_error(name, count, argv[1] ? argv[1] : dir);
		*status = 2;
	}
	else
		*status = 0;
	return (1);
}
