#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"

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

//those functions will be deleted after afterward
void			print_twodarr(char **map);
void			print_info(t_map *map);

//those are the main funtions
void			parce(char **map);
void			struct_initializer(t_map *map);

//error functions
void			print_error(char *error, int exitcode);

//parsing helper
t_color			ft_nb_take(char *str, int i);
int				ft_atoi_skip(char *str, int *i);
char			*ft_str_take(char *line, int i);
void			skip_spaces(char *str, int *i);

#endif
