/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:09:18 by hkawakit          #+#    #+#             */
/*   Updated: 2021/07/28 21:09:19 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (*(s + len))
		++len;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	if (!c)
		return ((char *)s + ft_strlen(s));
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		++s;
	}
	return (NULL);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*res;
	size_t	len;

	len = ft_strlen(s1);
	if (len > n)
		len = n;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	*(res + len) = '\0';
	while (len--)
		*(res + len) = *(s1 + len);
	return (res);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	*(res + len1 + len2) = '\0';
	while (len2--)
		*(res + len1 + len2) = *(s2 + len2);
	while (len1--)
		*(res + len1) = *(s1 + len1);
	free(s1);
	s1 = NULL;
	return (res);
}

void	ft_lstdelone(t_list **front, int fd)
{
	t_list	*lst;
	t_list	*tmp;

	if (front == NULL || *front == NULL)
		return ;
	lst = *front;
	if (lst->fd == fd)
	{
		*front = lst->next;
		free(lst);
		lst = NULL;
		return ;
	}
	if (lst->next == NULL)
		return ;
	while (lst->next->fd != fd)
		lst = lst->next;
	tmp = lst->next;
	lst->next = lst->next->next;
	free(tmp->text);
	tmp->text = NULL;
	free(tmp);
	tmp = NULL;
}
