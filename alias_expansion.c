#include "shell.h"

/**
 * apply_alias_expansion - applies alias expansion to argv
 * @argv: argument vector
 * @alias_tokens: tokens from alias value
 * @n_alias: number of tokens
 * @old_len: original length of argv
 */
void apply_alias_expansion(char **argv, char **alias_tokens, int n_alias,
		int old_len)
{
	int shift = n_alias - 1;
	int k;

	if (old_len + shift < 1024 && n_alias > 0)
	{
		if (shift > 0)
		{
			for (k = old_len; k >= 1; k--)
				argv[k + shift] = argv[k];
		}
		else if (shift < 0)
		{
			for (k = 1; k <= old_len; k++)
				argv[k + shift] = argv[k];
		}
		for (k = 0; k < n_alias; k++)
			argv[k] = alias_tokens[k];
	}
}

/**
 * check_alias - checks and expands aliases
 * @argv: argument vector
 * @aliases: aliases list
 *
 * Return: malloc'd string of alias value if expanded, NULL otherwise
 */
char *check_alias(char **argv, alias_t *aliases)
{
	char *alias_val, *alias_copy = NULL;
	int n_alias = 0, old_len = 0;
	char *alias_tokens[100], *t;

	if (!argv[0])
		return (NULL);
	alias_val = get_alias_value(argv[0], aliases);
	if (!alias_val)
		return (NULL);

	alias_copy = _strdup(alias_val);
	t = _strtok(alias_copy, " \t\n");
	while (t && n_alias < 100)
	{
		alias_tokens[n_alias++] = t;
		t = _strtok(NULL, " \t\n");
	}

	while (argv[old_len])
		old_len++;

	apply_alias_expansion(argv, alias_tokens, n_alias, old_len);
	return (alias_copy);
}
