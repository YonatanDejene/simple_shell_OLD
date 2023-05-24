#include "main.h"

/**
 * clr_inf - Intlz info_t structure.
 * @info: struct address
 */
void clr_inf(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * _setinf - Intlz info_t structure.
 * @info: structure add.
 * @av: Arg vector.
 */
void _setinf(info_t *info, char **av)
{
	int j = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_tow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = str_dup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (j = 0; info->argv && info->argv[j]; j++)
			;
		info->argc = j;

		rplc_als(info);
		rplc_vrs(info);
	}
}

/**
 * _frinfo – Free info_t structure fields.
 * @info: Structure add.
 * @all: True.
 */
void _frinfo(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			fr_ls(&(info->env));
		if (info->history)
			fr_ls(&(info->history));
		if (info->alias)
			fr_ls(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
