#include "main.h"

/**
 * gt_hstr - Get history.
 * @info: Parameter Structure.
 *
 * Return: Allocated string with history file.
 */

char *gt_hstr(info_t *info)
{
	char *buff, *dirr;

	dirr = get_env(info, "HOME=");
	if (!dirr)
		return (NULL);
	buff = malloc(sizeof(char) * (str_len(dirr) + str_len(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dirr);
	str_cat(buff, "/");
	str_cat(buff, HIST_FILE);
	return (buff);
}

/**
 * wr_hstr - Create file if there is already there append.
 * @info: Parameter structure.
 *
 * Return: If success 1, if not -1.
 */
int wr_hstr(info_t *info)
{
	ssize_t fd;
	char *filename = gt_hstr(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		puts_fd(node->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
