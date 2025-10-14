#include "../../../includes/cub3d.h"

char	**extract_map_from_parsed_data(char **all_content)
{
	int i = 0;
	int start = -1;
	int count = 0;

	while (all_content[i])
	{
		if (is_map_line(all_content[i]))
		{
			if (start == -1)
				start = i;
			count++;
		}
		i++;
	}
	if (count == 0)
		return (NULL);

	char **map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (NULL);

	i = 0;
	while (i < count)
	{
		map[i] = ft_strdup(all_content[start + i]);
		if (!map[i])
		{
			while (i > 0)
			{
				free(map[i - 1]);
				i--;
			}
			free(map);
			return (NULL);
		}
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	count_map_dimensions(char **map, int *rows, int *cols)
{
	*rows = 0;
	*cols = 0;
	while (map[*rows])
	{
		int len = ft_strlen(map[*rows]) - 1;
		if (len > *cols)
			*cols = len;
		(*rows)++;
	}
}

void	init_textures(t_data *d)
{
	int	i;

	i = 0;
	d->tex[TEX_NORTH].img = mlx_xpm_file_to_image(d->mlx_ptr,
		"textures/AnyConv.com__bluestone.xpm",&d->tex[TEX_NORTH].width, &d->tex[TEX_NORTH].height);
	d->tex[TEX_SOUTH].img = mlx_xpm_file_to_image(d->mlx_ptr,
		 "textures/AnyConv.com__colorstone.xpm", &d->tex[TEX_SOUTH].width, &d->tex[TEX_SOUTH].height);
	d->tex[TEX_EAST].img = mlx_xpm_file_to_image(d->mlx_ptr,
		 "textures/AnyConv.com__eagle.xpm", &d->tex[TEX_EAST].width, &d->tex[TEX_EAST].height);
	d->tex[TEX_WEST].img = mlx_xpm_file_to_image(d->mlx_ptr,
		 "textures/AnyConv.com__greystone.xpm", &d->tex[TEX_WEST].width, &d->tex[TEX_WEST].height);
	while (i < 4)
	{
		d->tex[i].addr = mlx_get_data_addr(d->tex[i].img, &d->tex[i].bpp, &d->tex[i].line_len, &d->endian);
		i++;
	}
}

void init_data_from_map(t_data *data, t_map *map_data)
{
	data->map = extract_map_from_parsed_data(map_data->all_content);
	if (!data->map)
		return ;
	count_map_dimensions(data->map, &data->rows, &data->cols);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr,
		SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	data->floor = map_data->floor;
	data->ceiling = map_data->ceiling;
	data->img = mlx_new_image(data->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->img_adr = mlx_get_data_addr(data->img,
		&data->bpp, &data->line_len, &data->endian);
	init_player_pos(data);
	data->speed = 1;
	data->input = (t_input){0, 0, 0, 0, 0, 0};
	mlx_hook(data->win_ptr, 2, 1L<<0, key_press, data);
	mlx_hook(data->win_ptr, 3, 1L<<1, key_release, data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_hook(data->win_ptr, 6, 1L << 6, mouse_move, data);
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	init_textures(data);
	mlx_loop_hook(data->mlx_ptr, update_loop, data);
}
