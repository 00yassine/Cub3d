NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -lXext -lX11 -lm
SRC = main.c get_next_line/get_next_line.c src/parsing/parce_the_map.c src/parsing/print_twodarr.c \
	src/parsing/struct_initializer.c src/parsing/parsing_helper.c src/parsing/checking_map.c \
	src/raycasting/start.c src/raycasting/src/1_init.c src/raycasting/src/3_draw_player.c \
	src/raycasting/src/2_draw_2D_map.c src/raycasting/src/4_input.c src/raycasting/src/5_update_player_pos.c\
	src/raycasting/src/6_get_distance.c
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all
