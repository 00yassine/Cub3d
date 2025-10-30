NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
MLX_INCLUDE = -I$(MLX_DIR)
LIBFT_DIR = libft
MLX_DIR = minilibx-linux

LIBFT = $(LIBFT_DIR)/libft.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC = main.c \
	get_next_line/get_next_line.c \
	src/parsing/parce_the_map.c \
	src/parsing/struct_initializer.c \
	src/parsing/parsing_helper.c \
	src/parsing/parsing_helper2.c \
	src/parsing/checking_map.c \
	src/raycasting/raycasting_entry.c \
	src/raycasting/src/init.c \
	src/raycasting/src/draw_minimap.c \
	src/raycasting/src/init_player.c \
	src/raycasting/src/input.c \
	src/raycasting/src/update_loop.c \
	src/raycasting/src/raycasting.c \
	src/raycasting/src/draw_3d.c \
	src/raycasting/src/draw_helpers.c \
	src/raycasting/src/utils.c \
	src/cleanup.c \
	src/parsing/extention_checker.c

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_DIR)/libmlx.a $(SRC)
	$(CC) $(CFLAGS) -Iincludes -I$(MLX_DIR) $(SRC) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(MLX_DIR)/libmlx.a:
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
