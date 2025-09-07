#include "../../../includes/cub3d.h"

void	put_px(char *img_adr, int line_len, int x, int y, unsigned int color)
{
	if (x < 0 || y < 0 || x >= 400 || y >= 400)
		return;

	((unsigned int *)img_adr)[y * (line_len / 4) + x] = color;
}

void	draw_tile(char *img_adr, int line_len, int px, int py, int color)
{
	int y = 0;
	while (y < TS)
	{
		int x = 0;
		while (x < TS)
		{
			put_px(img_adr, line_len, px + x, py + y, color);
			x++;
		}
		y++;
	}
}

void	draw_2d_map(t_data *data, char *img_adr, int line_len)
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
			draw_tile(img_adr, line_len, col * TS, row * TS, color);
			col++;
		}
		row++;
	}
}

int	is_wall(t_data *d, double x, double y)
{
	int map_x;
	int map_y;

	map_x = (int)floor(x / TS);
	map_y = (int)floor(y / TS);
	if (map_x < 0 || map_y < 0 || map_x >= d->cols || map_y >= d->rows)
		return (1);
	return (d->map[map_y][map_x] == '1');
}