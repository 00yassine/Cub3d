NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = src/main.c get_next_line/get_next_line.c src/parsing/parce_the_map.c src/parsing/print_twodarr.c \
	src/parsing/struct_initializer.c src/parsing/parsing_helper.c
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all
