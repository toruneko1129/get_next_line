#include "get_next_line.h"

static int	load_state(int fd, char **pre, char **res, char **buf)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(*pre);
		*pre = NULL;
		return (FAILED);
	}
	*res = ft_strndup(*pre, MAX_SIZE);
	free(*pre);
	*pre = NULL;
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
	size_t		i;

	cnt = ft_strlen(*res);
	i = 0;
	while (*res == NULL || ft_strchr(*res + i, '\n') == NULL)
	{
		i += cnt;
		cnt = read(fd, buf, BUFFER_SIZE);
		if (cnt == -1 || *res == NULL)
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
	free(buf);
	return (SUCCESS);
}

static char	*get_line_from_buf(char **pre, char **res)
{
	char	*line;
	char	*end;

	end = ft_strchr(*res, '\n');
	if (end == NULL)
		end = ft_strchr(*res, '\0');
	else if (*(end + 1))
	{
		*pre = ft_strndup(end + 1, MAX_SIZE);
		if (*pre == NULL)
		{
			free(*res);
			return (NULL);
		}
	}
	if (**res == '\0')
		line = NULL;
	else
		line = ft_strndup(*res, end - *res + 1);
	free(*res);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*pre = NULL;
	char		*line;
	char		*res;
	char		*buf;

	res = NULL;
	buf = NULL;
	if (load_state(fd, &pre, &res, &buf) || get_text_from_file(fd, &res, buf))
		return (NULL);
	line = get_line_from_buf(&pre, &res);
	return (line);
}
