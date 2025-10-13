#include "../../../includes/cub3d.h"

#define MINIMAP_SIZE        200
#define PLAYER_SIZE         4
#define MINIMAP_OFFSET_X    10
#define MINIMAP_OFFSET_Y    10
#define TILE_SIZE           64
#define SCALE_FACTOR        8.0  /* divide world coords by this to scale down */

void	my_mlx_pixel_put_minimap(t_data *d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return ;
	dst = d->img_adr + (y * d->line_len + x * (d->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	draw_square(t_data *d, int sx, int sy, int color, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put_minimap(d, sx + j, sy + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_player(t_data *d)
{
	int	i;
	int	j;
	int	cx;
	int	cy;

	cx = MINIMAP_OFFSET_X + MINIMAP_SIZE / 2 - PLAYER_SIZE / 2;
	cy = MINIMAP_OFFSET_Y + MINIMAP_SIZE / 2 - PLAYER_SIZE / 2;
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			my_mlx_pixel_put_minimap(d, cx + j, cy + i, 0xFF0000);
			j++;
		}
		i++;
	}
}

/* Scaled minimap centered on player */
void	draw_minimap(t_data *d)
{
	int		x;
	int		y;
	int		color;
	double	player_x;
	double	player_y;
	double	map_x;
	double	map_y;
	double	tile_screen_x;
	double	tile_screen_y;
	double	cell_size;

	cell_size = TILE_SIZE / SCALE_FACTOR;
	player_x = d->player.fpx;
	player_y = d->player.fpy;
	y = 0;
	while (y < d->rows)
	{
		x = 0;
		while (x < d->cols)
		{
			map_x = x * TILE_SIZE;
			map_y = y * TILE_SIZE;
			tile_screen_x = (map_x - player_x) / SCALE_FACTOR
				+ MINIMAP_OFFSET_X + MINIMAP_SIZE / 2;
			tile_screen_y = (map_y - player_y) / SCALE_FACTOR
				+ MINIMAP_OFFSET_Y + MINIMAP_SIZE / 2;
			if (tile_screen_x + cell_size < MINIMAP_OFFSET_X
				|| tile_screen_y + cell_size < MINIMAP_OFFSET_Y
				|| tile_screen_x > MINIMAP_OFFSET_X + MINIMAP_SIZE
				|| tile_screen_y > MINIMAP_OFFSET_Y + MINIMAP_SIZE)
			{
				x++;
				continue ;
			}
			if (d->map[y][x] == '1')
				color = 0x333333;
			else
				color = 0xAAAAAA;
			draw_square(d, (int)tile_screen_x, (int)tile_screen_y, color,
				(int)cell_size);
			x++;
		}
		y++;
	}
	draw_player(d);
}
