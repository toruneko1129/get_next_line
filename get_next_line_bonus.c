/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:09:11 by hkawakit          #+#    #+#             */
/*   Updated: 2021/08/01 22:19:17 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

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
	t_list	*last;
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
	return (SUCCESS);
}

char	*get_next_line(int fd)
{
	static t_map	*map = NULL;
	t_map			*res;
	char			*buf;

	res = NULL;
	if (fd < 0 || (ssize_t)BUFFER_SIZE <= 0 || load_state(fd, &map, &res))
		return (NULL);
	buf = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	if (get_text_from_file(res, buf))
	{
		ft_mapdelone(&map, &res);
		free(buf);
		return (NULL);
	}
	free(buf);
	return (NULL);
}
