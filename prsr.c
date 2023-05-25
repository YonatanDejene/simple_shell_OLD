#include "main.h"

/**
 * dp_char - Doubles characters.
 * @pathstr: PATH string.
 * @start: Starting indx.
 * @stop: Stopping indx.
 *
 * Return: Ptr.
 */
char *dp_char(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int j = 0, l = 0;

	for (l = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buf[l++] = pathstr[j];
	buf[l] = 0;
	return (buf);
}

/**
 * fnd_pth - Finds this command in the PATH string.
 * @info: Info structure.
 * @pathstr: PATH str.
 * @cmd: Command to find.
 *
 * Return: Full path of command if found or NULL
 */
char *fnd_pth(info_t *info, char *pathstr, char *cmd)
{
	int j = 0, crnt_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((str_len(cmd) > 2) && strt_w(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = dp_char(pathstr, crnt_pos, j);
			if (!*path)
				str_cat(path, cmd);
			else
			{
				str_cat(path, "/");
				str_cat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[j])
				break;
			crnt_pos = j;
		}
		j++;
	}
	return (NULL);
}
