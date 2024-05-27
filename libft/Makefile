NAME = libft.a

CC = cc

CFLAGS = -Werror -Wall -Wextra #-g3 -fsanitize=address

SRCS = ./gnl/get_next_line.c ./gnl/get_next_line_utils.c \
ft_strncmp.c ft_split.c ft_memcpy.c \
./ft_printf/ft_putchar.c ./ft_printf/ft_putstr.c ./ft_printf/ft_puthex.c \
./ft_printf/ft_putchex.c ./ft_printf/ft_putnbr.c ./ft_printf/ft_putptr.c \
./ft_printf/ft_unsigned.c ./ft_printf/ft_spf.c ./ft_printf/ft_printf.c \

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