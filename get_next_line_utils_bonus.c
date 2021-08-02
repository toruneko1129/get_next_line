/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:09:21 by hkawakit          #+#    #+#             */
/*   Updated: 2021/08/02 16:52:03 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*front;

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

void	ft_mapdelone(t_map **map, t_map **res)
{
	t_map	*pre;

	if (*map == *res)
	{
		*map = (*map)->next;
		ft_lstclear(&((*res)->lst));
		free(*res);
		*res = NULL;
		return ;
	}
	pre = *map;
	while (pre->next != *res)
		pre = pre->next;
	ft_lstclear(&((*res)->lst));
	pre->next = pre->next->next;
	free(*res);
	*res = NULL;
}

char	*ft_strchr(t_list *lst, int c)
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

int	ft_lstadd_back(t_list **last, char *buf, ssize_t cnt)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
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
