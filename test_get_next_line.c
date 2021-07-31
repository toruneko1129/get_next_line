#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main()
{
	int fd[5];

	fd[0] = open("./nonl", O_RDONLY);
	fd[1] = 1000;
	fd[2] = open("./nl", O_RDONLY);
	fd[3] = 2000;
	fd[4] = open("./munl", O_RDONLY);
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			int	k = (i % 2 ? 4 - j : j);
			char	*res = get_next_line(fd[k]);
			printf("%d %s\n", k, res);
			free(res);
		}
	}
	for (int i = 0; i < 5; ++i)
		close(fd[i]);
	system("leaks a.out");
}
