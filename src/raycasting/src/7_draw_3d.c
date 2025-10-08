#include "../../../includes/cub3d.h"

void my_mlx_pixel_put(char *img_adr, int x, int y, int color, int line_len, int bpp)
{
    void *dst;

    dst = img_adr + (y * line_len + x * (bpp / 8));
    *(unsigned int*)dst = color;
}

void	draw_wall_3d(t_data *d, int x, double dist)
{
	int line_height;
	int draw_start;
	int draw_end;

	if (dist < EPS)
		dist = EPS;
	line_height = (int)ceil((TS * SCREEN_HEIGHT) / dist);
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;

	// Ceiling
	for (int y = 0; y < draw_start; y++)
		my_mlx_pixel_put(d->img_adr, x, y, rgb_to_hex(&d->ceiling), d->line_len, d->bpp);
	// Wall
	for (int y = draw_start; y <= draw_end; y++)
		my_mlx_pixel_put(d->img_adr, x, y, 0x8B4513, d->line_len, d->bpp);
	// Floor
	for (int y = draw_end + 1; y < SCREEN_HEIGHT; y++)
		my_mlx_pixel_put(d->img_adr, x, y, rgb_to_hex(&d->floor), d->line_len, d->bpp);
}

void draw_3d(t_data *d)
{
	t_hit hit;
	double start_angle = d->player.angle - FOV / 2;
	double step = FOV / SCREEN_WIDTH;
	double cur_angle = start_angle;
	int x = 0;

	while (x < SCREEN_WIDTH)
	{
		get_distance(d, cur_angle, &hit);
		hit.dist *= cos(cur_angle - d->player.angle); // fisheye correction
		draw_wall_3d(d, x, hit.dist);
		cur_angle += step;
		x++;
	}
}

