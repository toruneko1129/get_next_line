/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:09:21 by hkawakit          #+#    #+#             */
/*   Updated: 2021/09/03 23:36:48 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	gnl_lstclear(t_buf **lst)
{
	t_buf	*front;

	front = *lst;
	while (front != NULL)
	{
		*lst = front->next;
		free(front->text);
		front->text = NULL;
		free(front);
		front = *lst;
	}
}

void	gnl_mapdelone(t_map **map, t_map **res)
{
	t_map	*pre;

	if (*map == *res)
	{
		*map = (*map)->next;
		gnl_lstclear(&((*res)->lst));
		free(*res);
		*res = NULL;
		return ;
	}
	pre = *map;
	while (pre->next != *res)
		pre = pre->next;
	gnl_lstclear(&((*res)->lst));
	pre->next = pre->next->next;
	free(*res);
	*res = NULL;
}

char	*gnl_strchr(t_buf *lst, int c)
{
	char	*s;

	if (lst == NULL)
		return (NULL);
	s = lst->text;
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		++s;
	}
	if (!c)
		return (s);
	return (NULL);
}

int	gnl_lstadd_back(t_buf **last, char *buf, ssize_t cnt)
{
	t_buf	*new;

	new = (t_buf *)malloc(sizeof(t_buf));
	if (new == NULL)
		return (FAILED);
	new->text = (char *)malloc((cnt + 1) * sizeof(char));
	if (new->text == NULL)
	{
		free(new);
		return (FAILED);
	}
	*(new->text + cnt) = '\0';
	while (cnt--)
		*(new->text + cnt) = *(buf + cnt);
	new->next = NULL;
	if (*last != NULL)
		(*last)->next = new;
	*last = new;
	return (SUCCESS);
}
