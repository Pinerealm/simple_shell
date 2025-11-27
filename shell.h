#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;

/* utils.c */
int _strlen(char *s);
void _puts(char *str);
void _eputs(char *str);
void print_number(int n);
void print_error(char *name, char *cmd, int count);

/* execute.c */
void execute_command(char **argv, char *name, int count);

#endif /* SHELL_H */
