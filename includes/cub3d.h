#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include <mlx.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

# define M_PI 3.14159265358979323846
# define TS         64
# define PLAYER_R   6
# define MOVE_SPEED 8.0
# define ROT_SPEED  0.1
# define MOUSE_SEN  0.5
# define EPS        1e-6
# define FOV        1.0471975512
# define SCREEN_WIDTH  1920
# define SCREEN_HEIGHT 1500

typedef struct s_point {
	double x;
	double y;
} t_point;

typedef struct s_player {
	double	angle;
	int		x;
	int		y;
	double	fpx;
	double	fpy;
} t_player;

typedef struct s_input {
	int k_up;
	int k_down;
	int k_left;
	int k_right;
	int k_strafe_left;
	int k_strafe_right;
} t_input;

typedef struct s_data {
	int			rows;
	int			cols;
	char		**map;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	void		*img_map2d;
	char		*img_adr;
	char		*img_map_adr;
	int			bpp;
	int			line_len;
	int			line_len_map;
	int			endian;
	t_player	player;
	t_input		input;
} t_data;

typedef struct s_ele_flags {
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
} t_ele_flags;

typedef struct s_color {
	int	r;
	int	g;
	int	b;
} t_color;

typedef struct s_map {
	char		**all_content;
	char		*no_player;
	char		*so_player;
	char		*we_player;
	char		*ea_player;
	t_color		floor;
	t_color		ceiling;
	t_ele_flags	ele;
} t_map;

/* runtime */
int		start(t_map *map_data);
int		update_loop(void *p);

/* init */
void	init_data_from_map(t_data *data, t_map *map_data);

/* input */
int		key_press(int key, void *p);
int		key_release(int key, void *p);
int		mouse_move(int x, int y, void *p);

/* drawing */
void	put_px(char *img_adr, int line_len, int x, int y, unsigned int color);
void	draw_tile(char *img_adr, int line_len, int px, int py, int color);
void	draw_2d_map(t_data *data, char *img_adr, int line_len);
void	draw_player(t_data *data, char *img_adr, int line_len);
void	init_player_pos(t_data *data);
void	draw_3d(t_data *d);
void	draw_wall_3d(t_data *d, int x, double dist);

/* raycasting */
double	get_distance(t_data *d, double ray_angle);
int		is_wall(t_data *d, double x, double y);
int		can_move(t_data *d, double x, double y, int r);

/* parsing */
t_map	*parce(char **map);
void	struct_initializer(t_map *map);
void	validate_map(char **map);
int		is_map_line(char *line);
t_color	ft_nb_take(char *str, int i);
int		ft_atoi_skip(char *str, int *i);
char	*ft_str_take(char *line, int i);
void	skip_spaces(char *str, int *i);

/* utils */
void	print_twodarr(char **map);
void	print_info(t_map *map);
void	print_error(char *error, int exitcode);

#endif
