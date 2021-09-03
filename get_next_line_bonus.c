/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:09:11 by hkawakit          #+#    #+#             */
/*   Updated: 2021/09/03 23:05:54 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	load_state(int fd, t_map **map, t_map **res)
{
	*res = *map;
	while (*res != NULL && (*res)->fd != fd)
		*res = (*res)->next;
	if (*res != NULL)
		return (SUCCESS);
	*res = (t_map *)malloc(sizeof(t_map));
	if (*res == NULL)
		return (FAILED);
	(*res)->fd = fd;
	(*res)->lst = NULL;
	(*res)->tlen = 0;
	(*res)->nlen = 0;
	(*res)->next = *map;
	*map = *res;
	return (SUCCESS);
}

static int	get_text_from_file(t_map *res, char *buf)
{
	t_buf	*last;
	char	*endl;
	ssize_t	cnt;

	last = res->lst;
	endl = ft_strchr(last, '\n');
	cnt = 1;
	while (endl == NULL && cnt)
	{
		cnt = read(res->fd, buf, (size_t)BUFFER_SIZE);
		if (cnt == -1)
			return (FAILED);
		*(buf + cnt) = '\0';
		if (ft_lstadd_back(&last, buf, cnt))
			return (FAILED);
		if (res->lst == NULL)
			res->lst = last;
		res->tlen += cnt;
		endl = ft_strchr(last, '\n');
	}
	if (endl != NULL)
		res->nlen = ft_strchr(last, '\0') - endl - 1;
	if (!res->tlen)
		return (FAILED);
	return (SUCCESS);
}

static int	save_state(t_map *res, char *text, size_t j)
{
	char	*save;
	t_buf	*new;
	size_t	i;

	save = (char *)malloc((res->nlen + 1) * sizeof(char));
	new = (t_buf *)malloc(sizeof(t_buf));
	if (new == NULL || save == NULL)
	{
		free(save);
		free(new);
		return (FAILED);
	}
	*(save + res->nlen) = '\0';
	i = 0;
	while (*(text + j))
		*(save + i++) = *(text + j++);
	new->text = save;
	new->next = NULL;
	ft_lstclear(&(res->lst));
	res->lst = new;
	res->tlen = res->nlen;
	res->nlen = 0;
	return (SUCCESS);
}

static int	get_line_from_buf(t_map *res, char **line)
{
	t_buf	*lst;
	size_t	i;
	size_t	j;

	*line = (char *)malloc((res->tlen - res->nlen + 1) * sizeof(char));
	if (*line == NULL)
		return (FAILED);
	*(*line + res->tlen - res->nlen) = '\0';
	lst = res->lst;
	i = 0;
	j = 0;
	while (i < res->tlen - res->nlen)
	{
		if (!*(lst->text + j))
		{
			lst = lst->next;
			j = 0;
		}
		*(*line + i++) = *(lst->text + j++);
	}
	if (res->nlen)
		return (save_state(res, lst->text, j));
	ft_lstclear(&(res->lst));
	return (SUCCESS);
}

char	*get_next_line(int fd)
{
	static t_map	*map = NULL;
	t_map			*res;
	char			*buf;
	char			*line;

	res = NULL;
	if (fd < 0 || (ssize_t)BUFFER_SIZE <= 0 || load_state(fd, &map, &res))
		return (NULL);
	buf = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	line = NULL;
	if (get_text_from_file(res, buf) || get_line_from_buf(res, &line))
	{
		ft_mapdelone(&map, &res);
		free(buf);
		free(line);
		return (NULL);
	}
	free(buf);
	if (res->lst == NULL)
		ft_mapdelone(&map, &res);
	return (line);
}
