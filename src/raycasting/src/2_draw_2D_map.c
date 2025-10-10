#include "../../../includes/cub3d.h"

void	draw_square(t_data *d, int x, int y, int color)
{
	int	i;
	int	j;
	int	size = 5;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(d->mlx_ptr, d->win_ptr, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_data *d)
{
	int	row;
	int	col;
	int	color;
	int	cell_size = 5;

	row = 0;
	while (d->map && d->map[row])
	{
		col = 0;
		while (d->map[row][col])
		{
			if (d->map[row][col] == '1')
				color = 0x333333;
			else
				color = 0xFFFFFF;
			draw_square(d, col * cell_size, row * cell_size, color);
			col++;
		}
		row++;
	}
	int px = d->player.x * cell_size;
	int py = d->player.y * cell_size;
	mlx_pixel_put(d->mlx_ptr, d->win_ptr, px, py, 0xFF0000);
}

int	render_frame(t_data *d)
{
	draw_minimap(d);
	return (0);
}
