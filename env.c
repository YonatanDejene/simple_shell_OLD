#include "main.h"

/**
 * my_env – Print current environment.
 * @info: Structure containing potential arguments.
 * Return: 0
 */
int my_env(info_t *info)
{
	prnt_ls_str(info->env);
	return (0);
}

/**
 * get_env – Get value of an environ variable.
 * @info: Structure containing potential arguments.
 *
 * Return: The value.
 */
char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *q;

	while (node)
	{
		q = strt_w(node->str, name);
		if (q && *q)
			return (q);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_stenv – Initialize or modify environmental variable.
 * @info: Structure containing potential arguments.
 *  Return: 0
 */
int my_stenv(info_t *info)
{
	if (info->argc != 3)
	{
		e_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unstenv – Removes environmental variables.
 * @info: Structure containing potential arguments.
 * Return: 0.
 */
int my_unstenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		e_puts("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		unset_env(info, info->argv[j]);

	return (0);
}

/**
 * p_env_list – Populate environmental linked lists
 * @info: Structure containing potential arguments.
 * Return: 0.
 */
int p_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_nd_en(&node, environ[i], 0);
	info->env = node;
	return (0);
}
