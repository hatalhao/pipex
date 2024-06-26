libft = libft.a

NAME = pipex

CC = cc

CFLAGS = -Werror -Wall -Wextra #-g3 -fsanitize=address

#SRC = $(wildcard *.c)
SRC = pipex.c utiles.c utiles2.c utiles3.c utiles4.c\

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) $(libft)
	$(CC) $(CFLAGS) $(OBJ) $(libft) -o $(NAME)

$(libft):
	make -s -C libft
	cd libft && mv libft.a ../

all: $(NAME)

clean: 
	rm -rf $(OBJ)
	make -s -C libft clean

fclean: clean
	rm -rf $(NAME) $(libft)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)