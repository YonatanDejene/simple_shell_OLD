#include "main.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
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
				e_eputs(av[0]);
				e_eputs(": 0: Can't open ");
				e_eputs(av[1]);
				e_eputchar('\n');
				e_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = j;
	}
	p_env_list(info);
	rd_hstr(info);
	msh(info, av);
	return (EXIT_SUCCESS);
}
