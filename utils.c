#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: string to check
 * Return: length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

/**
 * _puts - prints a string to stdout
 * @str: string to print
 */
void _puts(char *str)
{
	if (str)
		write(STDOUT_FILENO, str, _strlen(str));
}

/**
 * _eputs - prints a string to stderr
 * @str: string to print
 */
void _eputs(char *str)
{
	if (str)
		write(STDERR_FILENO, str, _strlen(str));
}

/**
 * print_number - prints an integer to stderr
 * @n: integer to print
 */
void print_number(int n)
{
	char c;

	if (n >= 10)
		print_number(n / 10);
	c = (n % 10) + '0';
	write(STDERR_FILENO, &c, 1);
}

/**
 * print_error - prints error message
 * @name: name of the shell program
 * @cmd: command that failed
 * @count: execution count
 */
void print_error(char *name, char *cmd, int count)
{
	_eputs(name);
	_eputs(": ");
	print_number(count);
	_eputs(": ");
	_eputs(cmd);
	_eputs(": not found\n");
}
