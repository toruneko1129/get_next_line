#include "get_next_line.h"

static int	load_state(int fd, char *pre, char **res, char **buf)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(pre);
		return (FAILED);
	}
	*res = ft_strndup(pre, MAX_SIZE);
	free(pre);
	pre = NULL;
	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*res == NULL || *buf == NULL)
	{
		free(*res);
		free(*buf);
		return (FAILED);
	}
	return (SUCCESS);
}

static int	get_text_from_file(int fd, char **res, char *buf)
{
	ssize_t		cnt;

	while (ft_strchr(*res, '\n') == NULL)
	{
		cnt = read(fd, buf, BUFFER_SIZE);
		if (cnt == -1)
		{
			free(*res);
			free(buf);
			return (FAILED);
		}
		else if (cnt == 0)
			break ;
		*(buf + cnt) = '\0';
		*res = ft_strjoin(*res, buf);
	}
	return (SUCCESS);
}

char	*get_next_line(int fd)
{
	static char	*pre = NULL;
	char		*res;
	char		*buf;

	res = NULL;
	buf = NULL;
	if (load_state(fd, pre, &res, &buf) || get_text_from_file(fd, &res, buf))
		return (NULL);
	return (res);
}
