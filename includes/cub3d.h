#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <math.h>
#include <sys/time.h>
#include <mlx.h>
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"

# define M_PI 3.14159265358979323846
# define FOV   1.0471975512 
# define TS 32
# define PLAYER_R 6
# define MOVE_SPEED 0.4
# define ROT_SPEED  0.008

typedef struct s_player {
	double	angle;
	int     x;
	int     y;
	double  fpx;
	double  fpy;
} t_player;

typedef struct s_input {
	int k_up;
	int k_down;
	int k_left;
	int k_right;
} t_input;

typedef struct s_ray
{
	int ray_len;
	double ray_angle;
	double start_angle;
	double end_angle;
	int 	px;
	int 	py;

} t_ray;

typedef struct s_data {
	int         rows;
	int         cols;
	char        **map;
	void        *mlx_ptr;
	void        *win_ptr;
	void        *img;
	char        *img_data;
	int         bpp;
	int         line_len;
	int         endian;
	t_player    player;
	long        last_ms;
	t_input     input;
	t_ray		ray;
} t_data;

typedef struct s_ele_flags
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_ele_flags;

typedef struct s_color {
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map
{
	char	**all_content;
	char	*no_player;
	char	*so_player;
	char	*we_player;
	char	*ea_player;
	t_color	floor;
	t_color	ceiling;
	t_ele_flags	ele;
}	t_map;

//raycasting
int		start(t_map *map_data);

//those functions will be deleted after afterward
void			print_twodarr(char **map);
void			print_info(t_map *map);

//those are the main funtions
t_map			*parce(char **map);
void			struct_initializer(t_map *map);
void			validate_map(char **map);

//raycasting integration
void			init_data_from_map(t_data *data, t_map *map_data);
int				start(t_map *map_data);
double get_distance(t_data *d, double ray_angle);


//error functions
void			print_error(char *error, int exitcode);

//parsing helper
int				is_map_line(char *line);
t_color			ft_nb_take(char *str, int i);
int				ft_atoi_skip(char *str, int *i);
char			*ft_str_take(char *line, int i);
void			skip_spaces(char *str, int *i);

/* player.c */
void	draw_player(t_data *data, char *img_data, int line_len);
void	init_player_pos(t_data *data);

/* map.c */
void	draw_tile(t_data *data, char *img_data, int line_len, int px, int py, int color);
void	draw_2d_map(t_data *data, char *img_data, int line_len);
int		is_wall(t_data *d, int x, int y);
int		can_move(t_data *d, int x, int y, int r);

/* input.c */
int		key_press(int key, void *p);
int		key_release(int key, void *p);

/* loop.c */
int		update_loop(void *p);


#endif
