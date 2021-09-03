/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:09:15 by hkawakit          #+#    #+#             */
/*   Updated: 2021/09/03 23:12:58 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# define MAX_SIZE -1
# define SUCCESS 0
# define FAILED 1

typedef struct s_buf
{
	char			*text;
	struct s_buf	*next;
}	t_buf;

typedef struct s_map
{
	int				fd;
	t_buf			*lst;
	size_t			tlen;
	size_t			nlen;
	struct s_map	*next;
}	t_map;

char	*get_next_line(int fd);
void	ft_lstclear(t_buf **lst);
void	ft_mapdelone(t_map **map, t_map **res);
char	*ft_strchr(t_buf *lst, int c);
int		ft_lstadd_back(t_buf **last, char *buf, ssize_t cnt);

#endif
