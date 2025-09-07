#include "../../../includes/cub3d.h"

char **extract_map_from_parsed_data(char **all_content)
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

void count_map_dimensions(char **map, int *rows, int *cols)
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

void init_data_from_map(t_data *data, t_map *map_data)
{
	data->map = extract_map_from_parsed_data(map_data->all_content);
	if (!data->map)
		return ;
	count_map_dimensions(data->map, &data->rows, &data->cols);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr,
		SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	data->img = mlx_new_image(data->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->img_map2d = mlx_new_image(data->mlx_ptr, 400, 400);
	data->img_adr = mlx_get_data_addr(data->img,
		&data->bpp, &data->line_len, &data->endian);
	data->img_map_adr = mlx_get_data_addr(data->img_map2d, &data->bpp, &data->line_len_map, &data->endian);
	init_player_pos(data);
	data->player.fpx = data->player.x;
	data->player.fpy = data->player.y;
	data->input = (t_input){0, 0, 0, 0, 0, 0};
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_map2d, 0, 0);
	mlx_hook(data->win_ptr, 2, 1L<<0, key_press, data);
	mlx_hook(data->win_ptr, 3, 1L<<1, key_release, data);
	mlx_loop_hook(data->mlx_ptr, update_loop, data);
}
