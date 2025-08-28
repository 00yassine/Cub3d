#include "../../../includes/cub3d.h"

void	put_px(t_data *data, char *img_data, int line_len, int x, int y, unsigned int color)
{
	if (x < 0 || y < 0 || x >= data->cols * TS || y >= data->rows * TS)
		return;

	((unsigned int *)img_data)[y * (line_len / 4) + x] = color;
}

void	draw_tile(t_data *data, char *img_data, int line_len, int px, int py, int color)
{
	int y = 0;
	while (y < TS)
	{
		int x = 0;
		while (x < TS)
		{
			put_px(data, img_data, line_len, px + x, py + y, color);
			x++;
		}
		y++;
	}
}

void	draw_2d_map(t_data *data, char *img_data, int line_len)
{
	int row = 0;
	int color;
	while (row < data->rows)
	{
		int col = 0;
		while (col < data->cols)
		{
			if (data->map[row][col] == '1')
				color =  0x8B4513;
			else
				color =  0xFFFFFF;
			draw_tile(data, img_data, line_len, col * TS, row * TS, color);
			col++;
		}
		row++;
	}
}

int	is_wall(t_data *d, int x, int y)
{
	int map_x = x / TS;
	int map_y = y / TS;
	
	if (map_x < 0 || map_y < 0 || map_x >= d->cols || map_y >= d->rows)
		return (1);
	
	return (d->map[map_y][map_x] == '1');
}

int	can_move(t_data *d, int x, int y, int r)
{
	return (!is_wall(d, x - r, y - r) && !is_wall(d, x + r, y - r) && 
			!is_wall(d, x - r, y + r) && !is_wall(d, x + r, y + r));
}
