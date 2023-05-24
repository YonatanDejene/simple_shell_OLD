#include "main.h"

/**
 * msh - Main shell.
 * @info: Parameter & return info structure.
 * @av: Argument vector from main().
 *
 * Return: If successful 0, if not 1.
 */

int msh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clr_inf(info);
		if (intractv(info))
			_puts("$ ");
		e_putchar(BUF_FLUSH);
		r = _gtinput(info);
		if (r != -1)
		{
			_setinf(info, av);
			builtin_ret = fnd_bltin(info);
			if (builtin_ret == -1)
				_fndcmd(info);
		}
		else if (intractv(info))
			_putchar('\n');
		_frinfo(info, 0);
	}
	wr_hstr(info);
	_frinfo(info, 1);
	if (!intractv(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * fnd_bltin - Finds Builtin comds.
 * @info: Parameter & return info structure.
 *
 * Return: -1 When builtin doesn’t exist,
 * 	0 When builtin executed successfully,
 * 	1 When builtin found but not successful,
 * 	2 When builtin signals exit().
 */
int fnd_bltin(info_t *info)
{
	int j, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", myext},
		{"env", my_env},
		{"help", _myhelp},
		{"history", myhstr},
		{"setenv", my_stenv},
		{"unsetenv", my_unstenv},
		{"cd", _mycd},
		{"alias", my_als},
		{NULL, NULL}
	};

	for (j = 0; builtintbl[j].type; j++)
		if (str_cmp(info->argv[0], builtintbl[j].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[j].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * _fndcmd - Finds comnd in PATH.
 * @info: Parameter & return info struct.
 *
 * Return: Nothing.
 */
void _fndcmd(info_t *info)
{
	char *path = NULL;
	int j, l;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (j = 0, l = 0; info->arg[j]; j++)
		if (!is_delim(info->arg[j], " \t\n"))
			l++;
	if (!l)
		return;

	path = fnd_pth(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		_frkcmd(info);
	}
	else
	{
		if ((intractv(info) || get_env(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			_frkcmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			prnt_err(info, "not found\n");
		}
	}
}

/**
 * _frkcmd - Forks executive thread to run command.
 * @info: Parameter & return info structure.
 *
 * Return: Nothing.
 */
void _frkcmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_env(info)) == -1)
		{
			_frinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				prnt_err(info, "Permission denied\n");
		}
	}
}
