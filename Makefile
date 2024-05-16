libft = libft.a

NAME = pipex

CC = cc

CFLAGS = -Werror -Wall -Wextra #-g3 -fsanitize=address

SRC = $(wildcard *.c)

OBJ = $(SRC=%c.%o)

$(libft):
	make -C libft
	cd libft && mv libft.a ../

$(NAME): $(OBJ) $(libft)
	$(CC) $(CFLAGS) $(OBJ) $(libft) -o $(NAME)

all: $(NAME)

clean: 
	rm -rf $(OBJ)
	make -C libft clean

fclean: clean
	rm -rf $(NAME) $(libft)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)