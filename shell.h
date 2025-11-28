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

/* string_utils.c */
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);

/* path.c */
char *_getenv(const char *name);
char *get_path(char *cmd);

/* builtins.c */
void print_env(void);

/* execute.c */
int execute_command(char **argv, char *name, int count);

#endif /* SHELL_H */
