# Simple Shell

A simple UNIX command interpreter written in C as part of the ALX Software Engineering curriculum. This shell replicates the core functionality of the `sh` shell, including command execution, argument parsing, and PATH resolution.

## Features

- **Command Execution**: Executes commands found in the system's `PATH` or via absolute/relative paths.
- **Argument Handling**: Supports commands with arguments (e.g., `ls -l /tmp`).
- **Environment**: Inherits the environment from the parent process.
- **Built-in Commands**:
  - `exit`: Exits the shell.
  - `env`: Prints the current environment variables.
  - `setenv`: Initializes a new environment variable or modifies an existing one.
  - `unsetenv`: Removes an environment variable.
  - `cd`: Changes the current directory. Supports `cd [dir]`, `cd` (home), and `cd -` (previous directory).
  - `alias`: Manages aliases. Supports `alias` (list), `alias name` (print value), and `alias name='value'` (define). Supports recursive alias expansion.
- **Variable Replacement**:
  - `$?`: Expands to the exit status of the most recently executed command.
  - `$$`: Expands to the process ID of the shell.
  - `$VAR`: Expands to the value of the environment variable `VAR`.
- **Command Separators**: Supports separating multiple commands with `;`, `&&`, and `||`.
- **Custom Implementation**: Uses custom implementations of `getline` and `strtok` to minimize standard library dependencies.
- **Error Handling**: Displays error messages matching the `sh` format.
- **Interactive & Non-Interactive Modes**: Works in a terminal or via pipes/scripts.
- **Memory Management**: Clean memory usage with no leaks.

## Installation

Clone the repository:

```bash
git clone https://github.com/Pinerealm/simple_shell.git
cd simple_shell
```

## Compilation

Compile the shell using `gcc` with the following flags:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o shell
```

## Usage

### Interactive Mode

Run the shell and type commands:

```bash
./shell
($) ls -l
total 40
-rw-rw-r-- 1 user user  234 Nov 27 12:00 AUTHORS
-rw-rw-r-- 1 user user 1234 Nov 27 12:00 execute.c
...
($) pwd
/home/user/simple_shell
($) cd ..
($) pwd
/home/user
($) setenv MYVAR hello
($) env
...
...
MYVAR=hello
($) ls; pwd
AUTHORS  execute.c  main.c  shell  shell.h
/home/user/simple_shell
($) echo $$
12345
($) echo $?
0
($) echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
($) exit
```

### Non-Interactive Mode

Pipe commands into the shell:

```bash
echo "ls -l" | ./shell
```

## File Structure

- **`main.c`**: Entry point. Handles the main loop, reading input, and parsing lines.
- **`execute.c`**: Handles process creation (`fork`) and execution (`execve`).
- **`builtins.c`**: Implementation of built-in commands (`env`, `setenv`, `unsetenv` logic).
- **`builtin_handlers.c`**: Handlers for built-in commands (`exit`, `cd`, `env` dispatch).
- **`alias_builtins.c`**: Handler for the `alias` built-in command.
- **`alias_expansion.c`**: Logic for expanding aliases in commands.
- **`alias_utils.c`**: Helper functions for alias management (storage, retrieval, printing).
- **`variable_expansion.c`**: Logic for variable replacement (`$?`, `$$`, `$VAR`).
- **`env_builtins.c`**: Environment variable management (`_setenv`, `_unsetenv`, `init_env`).
- **`path.c`**: Handles `PATH` environment variable searching and command resolution.
- **`getline.c`**: Custom implementation of the `getline` function using a static buffer.
- **`tokenizer.c`**: Custom implementation of `strtok` for splitting strings.
- **`string_utils.c`**: Custom string manipulation functions (`_strcpy`, `_strcat`, `_strdup`, etc.).
- **`utils.c`**: General utility functions (printing, error handling).
- **`shell.h`**: Header file containing function prototypes and standard library includes.

## Requirements

- Operating System: Linux (Ubuntu 20.04 LTS recommended)
- Compiler: GCC
- Code Style: Betty style

## Authors

- [Seyi Salami](https://github.com/Pinerealm)
- [Nasrullahi Olamide](https://github.com/nasrullahiolamide)
