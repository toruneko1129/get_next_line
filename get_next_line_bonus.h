#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# define MAX_SIZE -1
# define SUCCESS 0
# define FAILED 1

typedef struct s_list
{
	int				fd;
	char			*text;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strjoin(char *s1, const char *s2);
void	ft_lstdelone(t_list **begin, int fd);

#endif
