#include "main.h"

/**
 * intractv - If shell is intractv mode returns true.
 * @info: Address struct.
 *
 * Return: 1 If intractv mode, 0 if not.
 */
int intractv(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks if character is a delimeter or not.
 * @c: The char to be check.
 * @delim: The delimeter string.
 * Return: 1 If true, 0 if not.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha - Checks if the given input is alphabet or not.
 * @c: The character to be checked.
 * Return: 1 if c is alphabetic, 0 if not.
 */

int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * at - Convert a string to integer.
 * @s: String to be converted.
 * Return: 0 if no numbers in string, or converted numbers.
 */

int at(char *s)
{
	int x, sign = 1, f = 0, output;
	unsigned int res = 0;

	for (x = 0; s[x] != '\0' && f != 2; x++)
	{
		if (s[x] == '-')
			sign *= -1;

		if (s[x] >= '0' && s[x] <= '9')
		{
			f = 1;
			res *= 10;
			res += (s[x] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (sign == -1)
		output = -res;
	else
		output = res;

	return (output);
}
