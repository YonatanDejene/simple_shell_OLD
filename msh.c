#include "main.h"

/**
 * msh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int msh(info_t *info, char **av)
{
	ssize_t k = 0;
	int builtin = 0;

	while (k != -1 && builtin != -2)
	{
		clr_inf(info);
		if (intractv(info))
			_puts("$ ");
		_putchar(BUF_FLUSH);
		k = _gtinput(info);
		if (k != -1)
		{
			_setinf(info, av);
			builtin = fnd_bltin(info);
			if (builtin == -1)
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
	if (builtin == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = 
	{
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

	for (i = 0; builtintbl[i].type; i++)
		if (strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
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
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void _frkcmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_envron(info)) == -1)
		{
			_frinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
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
