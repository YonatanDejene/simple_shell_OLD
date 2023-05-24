#include "main.h"

/**
 * _inptbf - Buffers commands.
 * @info: Param structure.
 * @buf: Add of buf.
 * @len: Add of len.
 *
 * Return: Bytes.
 */
ssize_t _inptbf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USEget_ln
		r = get_ln(buf, &len_p, stdin);
#else
		r = get_ln(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			rm_cmnt(*buf);

			bld_hstr_ls(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * _gtinput - Gets line.
 * @info: Parameter structure.
 *
 * Return: Bytes.
 */
ssize_t _gtinput(info_t *info)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buff_p = &(info->arg), *pp;

	_putchar(BUF_FLUSH);
	r = _inptbf(info, &buff, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i;
		pp = buff + i;

		chck_chn(info, buff, &j, i, len);
		while (j < len)
		{
			if (_ischain(info, buff, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buff_p = pp;
		return (str_len(pp));
	}

	*buff_p = buff;
	return (r);
}

/**
 * _readbuf - Read buffers.
 * @info: Parameter structure.
 * @buf: The buffer.
 * @i: Size of the buffer.
 *
 * Return: r
 */
ssize_t _readbuf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, _READBUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_ln - Gets the next line.
 * @info: Parameter Structure.
 * @ptr: Address of pointer.
 * @length: Size of ptr.
 *
 * Return: s
 */
int get_ln(info_t *info, char **ptr, size_t *length)
{
	static char buf[_READBUF_SIZE];
	ssize_t r = 0, s = 0;
	char *pp = NULL, *new_pp = NULL, *c;
static size_t i, len;
	size_t k;

	pp = *ptr;
	if (pp && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = _readbuf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = str_chr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_pp = re_alloc(pp, s, s ? s + k : k + 1);
	if (!new_pp) /* MALLOC FAILURE! */
		return (pp ? free(pp), -1 : -1);

	if (s)
		strn_cat(new_pp, buf + i, k - i);
	else
		strn_cpy(new_pp, buf + i, k - i + 1);

	s += k - i;
	i = k;
	pp = new_pp;

	if (length)
		*length = s;
	*ptr = pp;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
