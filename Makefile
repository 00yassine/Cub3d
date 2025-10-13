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

$(NAME): $(SRC) $(LIBFT)
	@echo "Building minilibx if needed..."
	@if [ ! -f "$(MLX_DIR)/libmlx.a" ]; then \
		echo "MLX library not found. Building it manually..."; \
		cd $(MLX_DIR) && \
		if [ ! -f "Makefile.gen" ]; then \
			./configure > /dev/null 2>&1 || true; \
		fi && \
		make -f Makefile.gen libmlx.a > /dev/null 2>&1 || true; \
	fi
	@echo "Compiling $(NAME)..."
	$(CC) $(CFLAGS) -I$(MLX_DIR) -Iincludes $(SRC) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "Build successful!"

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ] && [ -f "$(MLX_DIR)/Makefile.gen" ]; then \
		make -C $(MLX_DIR) -f Makefile.gen clean; \
	fi

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
