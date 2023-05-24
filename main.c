#include "main.h"
/**
 * main – Entry.
 * @ac: ARG count.
 * @av: ATG vector.
 *
 * Return: if successful 0, if not 1.
 */

<<<<<<< HEAD
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };

	int fd = 2;

	asm ("mov %1, %0\n\t"
	"add $3, %0"
	: "=r" (fd)
	: "r" (fd));
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
=======
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
>>>>>>> 83f9b0dfce1f0ce864a628115ff5f67de9686633
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
<<<<<<< HEAD
				e_puts(av[0]);
				e_puts(": 0: Can't open ");
				e_puts(av[1]);
				e_putchar('\n');
				e_putchar(BUF_FLUSH);
=======
				e_eputs(av[0]);
				e_eputs(": 0: Can't open ");
				e_eputs(av[1]);
				e_eputchar('\n');
				e_eputchar(BUF_FLUSH);
>>>>>>> 83f9b0dfce1f0ce864a628115ff5f67de9686633
				exit(127);
			}
			return (EXIT_FAILURE);
		}
<<<<<<< HEAD
		info->readfd = fd;
	}
=======
		info->readfd = j;
	}
	p_env_list(info);
	rd_hstr(info);
>>>>>>> 83f9b0dfce1f0ce864a628115ff5f67de9686633
	msh(info, av);
	return (EXIT_SUCCESS);
}
