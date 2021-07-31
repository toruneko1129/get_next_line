NAME	=	a.out
SRCS	=	get_next_line_bonus.c get_next_line_utils_bonus.c test_get_next_line.c
OBJS	=	$(SRCS:.c=.o)
CC		=	gcc
CFLAG	=	-Wall -Wextra -Werror -D BUFFER_SIZE=2147483647

%.o: %.c
		$(CC) $(CFLAG) -c $<

$(NAME): $(OBJS)
		$(CC) -o $@ $^

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
