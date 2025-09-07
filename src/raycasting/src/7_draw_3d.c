#include "../../../includes/cub3d.h"

void my_mlx_pixel_put(char *img_adr, int x, int y, int color, int line_len, int bpp)
{
    char *dst;

    dst = img_adr + (y * line_len + x * (bpp / 8));
    *(unsigned int*)dst = color;
}

void	draw_wall_3d(t_data *d, int x, double dist)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;

	if (dist < EPS)
		dist = EPS;
	line_height = (int)((TS * SCREEN_HEIGHT) / dist);
	draw_start = -line_height / 2 + (SCREEN_HEIGHT) / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + (SCREEN_HEIGHT) / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;

	y = 0;
	while (y < draw_start)
	{
		my_mlx_pixel_put(d->img_adr, x, y, 0x87CEEB, d->line_len, d->bpp);
		y++;
	}
	while (y <= draw_end)
	{
		my_mlx_pixel_put(d->img_adr, x, y, 0x8B4513, d->line_len, d->bpp);
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(d->img_adr, x, y, 0x228B22, d->line_len, d->bpp);
		y++;
	}
}

void draw_3d(t_data *d)
{
	double start_angle = d->player.angle - FOV / 2;
	double step = FOV / SCREEN_WIDTH;
	double cur_angle = start_angle;
	int x = 0;

	while (x < SCREEN_WIDTH)
	{
		double dist = get_distance(d, cur_angle);
		draw_wall_3d(d, x, dist);
		cur_angle += step;
		x++;
	}
}

