/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:42:03 by elkharti          #+#    #+#             */
/*   Updated: 2025/10/31 10:53:21 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

# define M_PI 3.14159265358979323846
# define TS 64
# define PLAYER_R 6
# define MOVE_SPEED 2.0
# define ROT_SPEED 0.02
# define EPS 1e-6
# define FOV 1.0000000000
# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 800

# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_EAST 2
# define TEX_WEST 3
# define MINIMAP_SCALE 8
# define MINIMAP_RANGE 6
# define WIDTH 800
# define HEIGHT 600

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_player
{
	double	angle;
	int		x;
	int		y;
	double	fpx;
	double	fpy;
}	t_player;

typedef struct s_input
{
	int	k_up;
	int	k_down;
	int	k_left;
	int	k_right;
	int	k_view_left;
	int	k_view_right;
}	t_input;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		width;
	int		height;
}	t_tex;

typedef struct s_draw_minimap
{
	int		x;
	int		y;
	int		color;
	double	player_x;
	double	player_y;
	double	map_x;
	double	map_y;
	double	tile_x;
	double	tile_y;
	double	cell;
}	t_draw_minimap;

typedef struct s_draw_dir
{
	double	dir_len;
	double	start_x;
	double	start_y;
	double	end_x;
	double	end_y;
	double	dx;
	double	dy;
	double	steps;
	double	x_inc;
	double	y_inc;
	int		i;
}	t_draw_dir;

typedef struct s_data
{
	int			rows;
	int			cols;
	char		**map;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	char		*img_adr;
	int			bpp;
	int			line_len;
	int			endian;
	int			speed;
	t_player	player;
	t_color		floor;
	t_color		ceiling;
	t_input		input;
	t_tex		tex[4];
}	t_data;

typedef struct s_ele_flags
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_ele_flags;

typedef struct s_hit
{
	double	dist;
	double	hit_x;
	double	hit_y;
	int		is_vertical;
	int		tex_id;
	double	ray_angle;
}	t_hit;

typedef struct s_wall
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	t_tex	*tex;
	int		tex_x;
}	t_wall;

typedef struct s_map
{
	char		**all_content;
	char		*no_player;
	char		*so_player;
	char		*we_player;
	char		*ea_player;
	t_color		floor;
	t_color		ceiling;
	t_ele_flags	ele;
}	t_map;

int				raycasting_entry(t_map *map_data);
int				update_loop(void *p);
void			init_data_from_map(t_data *data, t_map *map_data);
void			count_map_dimensions(char **map, int *rows, int *cols);
int				key_press(int key, void *p);
int				key_release(int key, void *p);
int				close_window(void *p);
int				handle_mouse(int x, int y, void *param);
/*	drawing	*/
void			init_player_pos(t_data *data);
void			draw_3d(t_data *d, int x);
void			draw_minimap(t_data *d);
unsigned int	rgb_to_hex(t_color *c);
void			my_mlx_pixel_put(t_data *d, int x, int y, int color);
void			init_wall_params(t_data *d, t_hit *hit, t_wall *w);
void			calc_texture_x(t_hit *hit, t_wall *w);
void			draw_ceiling_floor(t_data *d, int x, t_wall *w);
void			draw_textured_wall(t_data *d, int x, t_wall *w);
void			my_mlx_pixel_put_minimap(t_data *d, int x, int y, int color);
void			draw_player_mini(t_data *d);

/*	raycasting	*/
void			get_distance(t_data *d, double ray_angle, t_hit *hit);
int				is_wall(t_data *d, double x, double y);

/*	parsing	*/
t_map			*parce(char **map);
void			struct_initializer(t_map *map);
void			validate_map(t_map *map);
int				is_map_line(char *line);
t_color			ft_nb_take(char *str, int i);
int				ft_atoi_skip(char *str, int *i);
char			*ft_str_take(char *line, int i);
void			skip_spaces(char *str, int *i);
void			ft_ex_checker(char *str);
void			fill_player_str(t_map *map_list);
int				check_map_structer(t_map *map_stu, char **map);

/*	utils	*/
void			print_error(char *error);
void			set_vertical_hit(t_hit *hit, t_point x_int, double x_dist);

/*	cleanup	*/
void			cleanup_data(t_data *data);

/*	garbage collector	*/
void			*gc_malloc(size_t size);
void			gc_free(void *ptr);
void			gc_free_all(void);

#endif
