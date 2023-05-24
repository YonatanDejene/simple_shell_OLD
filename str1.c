#include "main.h"

/**
 * _strcpy - Copy str.
 * @dest: Destination.
 * @src: Source.
 *
 * Return: Pointer.
 */
char *_strcpy(char *dest, char *src)
{
	int h = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[h])
	{
		dest[h] = src[h];
		h++;
	}
	dest[h] = 0;
	return (dest);
}

/**
 * str_dup - Doubles String.
 * @str: String to be doubled.
 *
 * Return: Pointer.
 */
char *str_dup(const char *str)
{
	int lng = 0;
	char *rt;

	if (str == NULL)
		return (NULL);
	while (*str++)
		lng++;
	rt = malloc(sizeof(char) * (lng + 1));
	if (!rt)
		return (NULL);
	for (lng++; lng--;)
		rt[lng] = *--str;
	return (rt);
}

/**
 * _puts - Print given string.
 * @str: String to be printed.
 *
 * Return: Void.
 */
void _puts(char *str)
{
	int h = 0;

	if (!str)
		return;
	while (str[h] != '\0')
	{
		_putchar(str[h]);
		h++;
	}
}

/**
 * _putchar - Writes charater.
 * @c: Character to be written.
 *
 * Return: 1 if success, -1 is returned if not.
 */
int _putchar(char c)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buff, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buff[j++] = c;
	return (1);
}
