#include "get_next_line_bonus.h"

static t_list	*load_text(int fd, t_list **begin)
{
	t_list	*lst;
	t_list	*new;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	lst = *begin;
	while (lst != NULL)
	{
		if (lst->fd == fd)
			return (lst);
		lst = lst->next;
	}
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->text = NULL;
	new->next = *begin;
	*begin = new;
	return (new);
}

static int	load_state(t_list *pre, char **res, char **buf)
{
	*res = ft_strndup(pre->text, MAX_SIZE);
	free(pre->text);
	pre->text = NULL;
	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*res == NULL || *buf == NULL)
	{
		free(*res);
		free(*buf);
		return (FAILED);
	}
	return (SUCCESS);
}

static int	get_text_from_file(int fd, char **res, char *buf, t_list **begin)
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
			ft_lstdelone(begin, fd);
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

static char	*get_line_from_buf(t_list *pre, char **res, t_list **begin)
{
	char	*line;
	char	*end;

	end = ft_strchr(*res, '\n');
	if (end == NULL)
		end = ft_strchr(*res, '\0');
	if (*end && *(end + 1))
	{
		pre->text = ft_strndup(end + 1, MAX_SIZE);
		if (pre->text == NULL)
		{
			free(*res);
			return (NULL);
		}
	}
	else
		ft_lstdelone(begin, pre->fd);
	if (**res == '\0')
		line = NULL;
	else
		line = ft_strndup(*res, end - *res + 1);
	free(*res);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	char			*line;
	t_list			*pre;
	char			*res;
	char			*buf;

	pre = load_text(fd, &lst);
	if (pre == NULL)
	{
		while (lst != NULL)
			ft_lstdelone(&lst, lst->fd);
		return (NULL);
	}
	res = NULL;
	buf = NULL;
	if (load_state(pre, &res, &buf) || get_text_from_file(fd, &res, buf, &lst))
		return (NULL);
	line = get_line_from_buf(pre, &res, &lst);
	return (line);
}
