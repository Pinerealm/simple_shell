#include "shell.h"

/**
 * free_aliases - frees the aliases list
 * @aliases: head of aliases list
 */
void free_aliases(alias_t *aliases)
{
	alias_t *node = aliases;
	alias_t *next;

	while (node)
	{
		next = node->next;
		free(node->name);
		free(node->value);
		free(node);
		node = next;
	}
}

/**
 * get_alias_value - gets the value of an alias
 * @name: alias name
 * @aliases: head of aliases list
 *
 * Return: value or NULL
 */
char *get_alias_value(char *name, alias_t *aliases)
{
	alias_t *node = aliases;

	while (node)
	{
		if (_strcmp(node->name, name) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_alias - sets or updates an alias
 * @name: alias name
 * @value: alias value
 * @aliases: pointer to head of aliases list
 *
 * Return: 0 on success, -1 on failure
 */
int set_alias(char *name, char *value, alias_t **aliases)
{
	alias_t *node = *aliases;
	alias_t *new_node;

	while (node)
	{
		if (_strcmp(node->name, name) == 0)
		{
			free(node->value);
			node->value = _strdup(value);
			return (0);
		}
		node = node->next;
	}

	new_node = malloc(sizeof(alias_t));
	if (!new_node)
		return (-1);

	new_node->name = _strdup(name);
	new_node->value = _strdup(value);
	new_node->next = *aliases;
	*aliases = new_node;
	return (0);
}

/**
 * print_alias - prints an alias
 * @name: alias name
 * @aliases: head of aliases list
 *
 * Return: 0 on success, 1 if not found
 */
int print_alias(char *name, alias_t *aliases)
{
	alias_t *node = aliases;

	while (node)
	{
		if (_strcmp(node->name, name) == 0)
		{
			_puts(node->name);
			_puts("='");
			_puts(node->value);
			_puts("'\n");
			return (0);
		}
		node = node->next;
	}
	return (1);
}

/**
 * print_all_aliases - prints all aliases
 * @aliases: head of aliases list
 */
void print_all_aliases(alias_t *aliases)
{
	alias_t *node = aliases;

	while (node)
	{
		_puts(node->name);
		_puts("='");
		_puts(node->value);
		_puts("'\n");
		node = node->next;
	}
}
