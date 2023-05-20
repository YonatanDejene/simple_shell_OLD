#include "main.h"
#include <sys/wait.h>

void prompt(char **ax, char **envi)
{
	char *str = NULL;
	int j, stats;
	size_t n = 0;
	char *argv[] = {NULL, NULL};
	ssize_t number_char;
	pid_t pid;

	while (1)
	{
		printf("cisfun$ ");

		number_char = getline(&str, &n, stdin);
		if (number_char == -1)
		{
			free(str);
			exit(EXIT_FAILURE);
		}
		while (str[j])
		{
			if (str[j] == '\n')
				str[j] = 0;
			j++;
		}
		pid = fork();
		argv[0] = str;
		if (pid == -1)
		{
			free(str);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execve(argv[0], argv, envi) == -1)
				printf("%s: No such file or directory\n", ax[0]);
		}
		else
			wait(&stats);
	}
}

