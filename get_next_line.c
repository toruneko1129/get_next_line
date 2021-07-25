#include "get_next_line.h"
#include <stdio.h>

static int	load_state(int fd, char *pre, char **res, char **buf)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(pre);
		pre = NULL;
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
		printf("%zd\n", cnt);
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
		if (*res == NULL)
		{
			free(buf);
			return (FAILED);
		}
	}
	free(buf);
	return (SUCCESS);
}

static void	get_line_from_buf(char **pre, char **res, char **line)
{
	size_t	len;
	char	*end;

	len = ft_strlen(*res);
	if (!len)
	{
		free(*res);
		return ;
	}
	end = ft_strchr(*res, '\n');
	if (end == NULL)
		end = *res + len;
	else if (*(end + 1))
	{
		*pre = ft_strndup(end + 1, MAX_SIZE);
		if (*pre == NULL)
		{
			free(*res);
			return ;
		}
	}
	*line = ft_strndup(*res, end - *res + 1);
	free(*res);
}

char	*get_next_line(int fd)
{
	static char	*pre = NULL;
	char		*line;
	char		*res;
	char		*buf;

	res = NULL;
	buf = NULL;
	if (load_state(fd, pre, &res, &buf) || get_text_from_file(fd, &res, buf))
		return (NULL);
	line = NULL;
	get_line_from_buf(&pre, &res, &line);
	return (line);
}
