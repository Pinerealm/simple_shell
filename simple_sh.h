#ifndef SIMPLE_SH_H
#define SIMPLE_SH_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUFF_SIZE 1024 /**< buffer size */
#define MAX_ARGS 64 /**< maximum number of arguments */

/* FUNCTION PROTOTYPES */
void prompt(void);
void execute(char **args, char **envp);
void print_env(char **env);
void parse_str(char *input_str, char **args);


#endif /* SIMPLE_SH_H */

