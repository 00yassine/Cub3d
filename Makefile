NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
MLX_INCLUDE = -I$(MLX_DIR)
SRC = main.c get_next_line/get_next_line.c src/parsing/parce_the_map.c src/parsing/print_twodarr.c \
	src/parsing/struct_initializer.c src/parsing/parsing_helper.c src/parsing/checking_map.c \
	src/raycasting/start.c src/raycasting/src/1_init.c src/raycasting/src/3_draw_player.c \
	src/raycasting/src/2_draw_2D_map.c src/raycasting/src/4_input.c src/raycasting/src/5_update_player_pos.c\
	src/raycasting/src/6_get_distance.c src/raycasting/src/7_draw_3d.c src/raycasting/src/9_utils.c\
	src/raycasting/src/8_add_textures.c
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(MLX_DIR)/libmlx.a:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Error: MLX directory not found. Please run:"; \
		echo "git clone https://github.com/42Paris/minilibx-linux.git mlx && cd mlx && make"; \
		exit 1; \
	fi
	make -C $(MLX_DIR)

$(NAME): $(SRC) $(LIBFT) $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) $(MLX_INCLUDE) $(SRC) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean; fi

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
