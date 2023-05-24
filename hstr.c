#include "main.h"

/**
 * gt_hstr – Get history.
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

/**
 * rd_hstr - Read history.
 * @info: Parameter structure.
 *
 * Return: History count on success, 0 of failure.
 */
int rd_hstr(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = gt_hstr(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			bld_hstr_ls(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		bld_hstr_ls(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		dlt_nd_at_indx(&(info->history), 0);
	renum_hstr(info);
	return (info->histcount);
}
