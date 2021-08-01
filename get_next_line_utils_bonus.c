/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:09:21 by hkawakit          #+#    #+#             */
/*   Updated: 2021/08/01 16:21:34 by hkawakit         ###   ########.fr       */
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
		free(*res);
		*res = NULL;
		return ;
	}
	pre = *map;
	while (pre->next != *res)
		pre = pre->next;
	pre->next = (*res)->next;
	ft_lstclear(&((*res)->lst));
	free(*res);
	*res = NULL;
}
