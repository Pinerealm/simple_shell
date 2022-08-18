#ifndef SIMPLE_SH_H
#define SIMPLE_SH_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_INPUT 1024
#define MAX_ARGS 20 /**< maximum number of arguments */
#define TRUE 1
#define INTERACTIVE 1 /**< shell is interactive */

/**
 * struct builtin - builtin commands
 *
 * @name: name of the builtin command
 * @func: function to execute the builtin command
 */
typedef struct builtin
{
	char *name;
	int (*func)(char **args, char **envp);
} builtin_t;

/**
 * struct env - environment variables
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 */
typedef struct env
{
	char *name;
	char *value;
} env_t;

/**
 * struct path - path to the executable
 *
 * @name: name of the executable
 * @path: path to the executable
 */
typedef struct path
{
	char *name;
	char *path;
} path_t;


/* FUNCTION PROTOTYPES */
void prompt(void);
void execute(char **args, char **argv);
void print_env(char **env);
void parse_str(char *input_str, char **args);

void is_interactive(int *status);
ssize_t get_input(char *input_line, char **argv);
void init_arr(char **args, int size);
int handle_builtins(char **args);

/* string functions */
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);
void trim(char *str);

#endif /* SIMPLE_SH_H */
