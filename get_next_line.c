#include "get_next_line.h"

static t_list	*load_state(int fd, t_list **front)
{
	t_list	*lst;
	t_list	*new;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	lst = *front;
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
	new->next = *front;
	*front = new;
	return (new);
}

static int	load_text(t_list **front, t_list *pre, char **res, char **buf)
{
	*res = ft_strndup(pre->text, MAX_SIZE);
	free(pre->text);
	pre->text = NULL;
	*buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (*res == NULL || *buf == NULL)
	{
		free(*res);
		free(*buf);
		ft_lstdelone(front, pre->fd);
		return (FAILED);
	}
	return (SUCCESS);
}

static int	get_text_from_file(int fd, t_list **front, char **res, char *buf)
{
	ssize_t		cnt;
	size_t		i;

	cnt = ft_strlen(*res);
	i = 0;
	while (*res == NULL || ft_strchr(*res + i, '\n') == NULL)
	{
		i += cnt;
		if (*res != NULL)
			cnt = read(fd, buf, BUFFER_SIZE);
		if (cnt == -1 || *res == NULL)
		{
			free(*res);
			free(buf);
			ft_lstdelone(front, fd);
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

static char	*get_line_from_buf(t_list **front, t_list *pre, char **res)
{
	char	*line;
	char	*end;

	end = ft_strchr(*res, '\n');
	if (end == NULL)
		end = ft_strchr(*res, '\0');
	if (*end == '\n' && *(end + 1))
	{
		pre->text = ft_strndup(end + 1, MAX_SIZE);
		if (pre->text == NULL)
		{
			free(*res);
			ft_lstdelone(front, pre->fd);
			return (NULL);
		}
	}
	else
		ft_lstdelone(front, pre->fd);
	line = NULL;
	if (**res)
		line = ft_strndup(*res, end - *res + 1);
	if (**res && line == NULL)
		ft_lstdelone(front, pre->fd);
	free(*res);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	t_list			*pre;
	char			*res;
	char			*buf;

	pre = load_state(fd, &lst);
	if (pre == NULL)
		return (NULL);
	res = NULL;
	buf = NULL;
	if (load_text(&lst, pre, &res, &buf))
		return (NULL);
	if (get_text_from_file(fd, &lst, &res, buf))
		return (NULL);
	return (get_line_from_buf(&lst, pre, &res));
}
