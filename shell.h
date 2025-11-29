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

#define READ_BUF_SIZE 1024

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

/* string_utils_2.c */
int _atoi(char *s);

/* tokenizer.c */
char *_strtok(char *str, char *delim);

/* path.c */
char *_getenv(const char *name);
char *get_path(char *cmd);

/* builtins.c */
void print_env(void);

/* env_builtins.c */
int _setenv(char *name, char *value);
int _unsetenv(char *name);
void init_env(char **env);
void free_env(void);

/* builtin_handlers.c */
int handle_exit(char **argv, int *status, char *name, int count);
int handle_env_commands(char **argv, int *status);

/* getline.c */
ssize_t _getline(char **lineptr, size_t *n, int fd);

/* execute.c */
int execute_command(char **argv, char *name, int count);

/* utils.c */
int _strlen(char *s);
void _puts(char *str);
void _eputs(char *str);
void print_number(int n);
void print_error(char *name, char *cmd, int count);

/* utils_2.c */
void print_exit_error(char *name, int count, char *arg);


#endif /* SHELL_H */
