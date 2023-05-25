#include "main.h"

/**
 * e_puts - initial input.
 * @str: String to be printed.
 *
 * Return: Nothing.
 */
void e_puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		e_putchar(str[j]);
		j++;
	}
}

/**
 * e_putchar - Writes character c.
 * @c: The character to be written.
 *
 * Return: If success 1 if not -1 is returned, and errno is set appropriately.
 */
int e_putchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * put_fd - Write the character c.
 * @c: The character to be written.
 * @fd: Filedescriptor which c is to be written on.
 *
 * Return: If success 1,if not -1 is returned, and errno is set appropriately.
 */
int put_fd(char c, int fd)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buff, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buff[j++] = c;
	return (1);
}

/**
 * puts_fd - Print input string.
 * @str: String to be printed.
 * @fd: Filedescriptor.
 *
 * Return: Num of chars put.
 */
int puts_fd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += put_fd(*str++, fd);
	}
	return (j);
}
