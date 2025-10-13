#include "../../../includes/cub3d.h"

#define MAX_MINIMAP_WIDTH 200
#define MAX_MINIMAP_HEIGHT 200
#define PLAYER_SIZE 4
#define MINIMAP_OFFSET_X 10
#define MINIMAP_OFFSET_Y 10

/* Draw a single pixel in the image */
void	my_mlx_pixel_put_minimap(t_data *d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return ;
	dst = d->img_adr + (y * d->line_len + x * (d->bpp / 8));
	*(unsigned int *)dst = color;
}

/* Draw one square cell of the minimap */
static void	draw_square(t_data *d, int x, int y, int color, int cell_size)
{
	int	i;
	int	j;
	int	sx;
	int	sy;

	sy = y * cell_size;
	i = 0;
	while (i < cell_size)
	{
		sx = x * cell_size;
		j = 0;
		while (j < cell_size)
		{
			my_mlx_pixel_put_minimap(d, sx + j, sy + i, color);
			j++;
		}
		i++;
	}
}

/* Draw the player on the minimap */
static void	draw_player(t_data *d, int cell_size)
{
	int		i;
	int		j;
	double	map_x;
	double	map_y;
	int		px;
	int		py;

	map_x = d->player.fpx / 64.0;
	map_y = d->player.fpy / 64.0;
	px = (int)(map_x * cell_size - (PLAYER_SIZE / 2));
	py = (int)(map_y * cell_size - (PLAYER_SIZE / 2));

	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			my_mlx_pixel_put_minimap(d, px + j, py + i, 0xFF0000);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_data *d)
{
	int	x;
	int	y;
	int	color;
	int	cell_size;
	int	cell_x;
	int	cell_y;

	cell_x = MAX_MINIMAP_WIDTH / d->cols;
	cell_y = MAX_MINIMAP_HEIGHT / d->rows;
	if (cell_x < cell_y)
		cell_size = cell_x;
	else
		cell_size = cell_y;
	if (cell_size < 1)
		cell_size = 1;
	y = 0;
	while (y < d->rows)
	{
		x = 0;
		while (x < d->cols)
		{
			if (d->map[y][x] == '1')
				color = 0x333333;
			else
				color = 0xAAAAAA;
			draw_square(d, x, y, color, cell_size);
			x++;
		}
		y++;
	}
	draw_player(d, cell_size);
}
