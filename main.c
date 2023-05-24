#include "main.h"

/**
 * main - entery point
 * @ac: ARG count.
 * @av: ATG vector.
 *
 * Return: if successful 0, if not 1.
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };

	int j = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (j)
		: "r" (j));
	if (ac == 2)
	{
		j = open(av[1], O_RDONLY);
		if (j == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				e_puts(av[0]);
				e_puts(": 0: Can't open ");
				e_puts(av[1]);
				e_putchar('\n');
				e_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = j;
	}
	//p_env_list(info);
	//rd_hstr(info);
	msh(info, av);
	return (EXIT_SUCCESS);
}
