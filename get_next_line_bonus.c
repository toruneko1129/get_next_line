/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:09:11 by hkawakit          #+#    #+#             */
/*   Updated: 2021/08/01 17:49:23 by hkawakit         ###   ########.fr       */
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
	(*res)->next = *map;
	*map = *res;
	return (SUCCESS);
}

static int	get_text_from_file(t_map **map, char *buf, t_map **res)
{
	t_list	*last;
	ssize_t	cnt;

	last = (*res)->lst;
	while (last == NULL || ft_strchr(last->text, '\n'))
	{
		cnt = read((*res)->fd, buf, (size_t)BUFFER_SIZE);
		if (cnt == -1)
		{
			free(buf);
			ft_mapdelone(map, res);
			return (FAILED);
		}
		else if (cnt == 0)
			break;
		*(buf + cnt) = '\0';
	}
	return (SUCCESS);
}

char	*get_next_line(int fd)
{
	static t_map	*map = NULL;
	char			*buf;
	t_map			*res;

	if (fd < 0 || (ssize_t)BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	res = NULL;
	if (load_state(fd, &map, &res) || get_text_from_file(&map, buf, &res))
		return (NULL);
	return (NULL);
}
