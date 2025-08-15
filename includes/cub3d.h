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
	bool	no;
	bool	so;
	bool	we;
	bool	ea;
	bool	f;
	bool	c;
}	t_ele_flags;

typedef struct s_map
{
	char	**all_content;
	t_ele_flags	ele;
}	t_map;

//those functions will be deleted after afterward
void	print_twodarr(char **map);

//those are the main funtions
void	parce(char **map);

//error functions
void print_error(char *error, int exitcode);

#endif
