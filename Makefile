libft = libft.a

NAME = pipex

CC = cc

BONUS = pipex_bonus

CFLAGS = -Werror -Wall -Wextra #-g3 -fsanitize=address

SRC = $(wildcard src/*.c)

SRC_BONUS =  $(filter-out src/main_mandatory.c, $(wildcard bonus/*.c src/*.c))

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)


# ifeq ($(BONUS),true)
#     bonus: $(BONUS)
# else
#     all: $(NAME)
# endif

# all: $(if$(filter $(BONUS),true),bonus,all)
all: $(NAME)

bonus: $(BONUS)

$(NAME): $(OBJ) $(libft)
	$(CC) $(CFLAGS) $(OBJ) $(libft) -o $(NAME)

$(BONUS): $(OBJ_BONUS) $(libft)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(libft) -o $(BONUS)

$(libft):
	make -s -C libft
	cd libft && mv libft.a ../

clean: 
	rm -rf $(OBJ)
	make -s -C libft clean

fclean: clean
	rm -rf $(NAME) $(libft)
	rm -rf $(BONUS)


re: fclean all

.PHONY: all bonus clean fclean re

.SECONDARY: $(OBJ) $(OBJ_BONUS)