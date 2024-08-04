NAME = libft.a

CC = cc

CFLAGS = -Werror -Wall -Wextra #-g3 -fsanitize=address

SRCS = $(wildcard *.c ./gnl/*.c ./ft_printf/*.c)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		ar -rcs $(NAME) $?

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJS)