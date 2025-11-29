#include "shell.h"

/**
 * print_exit_error - prints error message for exit
 * @name: name of the shell program
 * @count: execution count
 * @arg: argument that failed
 */
void print_exit_error(char *name, int count, char *arg)
{
	_eputs(name);
	_eputs(": ");
	print_number(count);
	_eputs(": exit: Illegal number: ");
	_eputs(arg);
	_eputs("\n");
}

/**
 * print_cd_error - prints error message for cd
 * @name: name of the shell program
 * @count: execution count
 * @arg: argument that failed
 */
void print_cd_error(char *name, int count, char *arg)
{
	_eputs(name);
	_eputs(": ");
	print_number(count);
	_eputs(": cd: can't cd to ");
	_eputs(arg);
	_eputs("\n");
}
