/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_draw_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:29:42 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/14 10:31:52 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	my_mlx_pixel_put(char *img_adr, int x, int y, int color, int line_len, int bpp)
{
	char	*dst;

	dst = img_adr + (y * line_len + x * (bpp / 8));
	*(unsigned int *)dst = color;
}

static void	draw_wall_3d(t_data *d, int x, t_hit *hit)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	t_tex	*tex;
	int	tex_x;
	double	step;
	double	tex_pos;

	if (hit->dist < EPS)
		hit->dist = EPS;
	line_height = (int)((TS * SCREEN_HEIGHT) / hit->dist);
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	int	y = 0;
	while (y < draw_start)
	{
		my_mlx_pixel_put(d->img_adr, x, y, rgb_to_hex(&d->ceiling), d->line_len, d->bpp);
		y++;
	}
	tex = &d->tex[hit->tex_id];
	if (hit->is_vertical)
		tex_x = (int)fmod(hit->hit_y, TS) * tex->width / TS;
	else
		tex_x = (int)fmod(hit->hit_x, TS) * tex->width / TS;
	if ((hit->is_vertical && cos(hit->ray_angle) < 0) ||
		(!hit->is_vertical && sin(hit->ray_angle) > 0))
		tex_x = tex->width - tex_x - 1;
	step = (double)tex->height / line_height;
	tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
	y = draw_start;
	while (y <= draw_end)
	{
		int	tex_y = (int)tex_pos % tex->height;
		int	color = *(unsigned int *)(tex->addr + tex_y * tex->line_len + tex_x * (tex->bpp / 8));
		my_mlx_pixel_put(d->img_adr, x, y, color, d->line_len, d->bpp);
		tex_pos += step;
		y++;
	}
	y = draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(d->img_adr, x, y, rgb_to_hex(&d->floor), d->line_len, d->bpp);
		y++;
	}
}

void	draw_3d(t_data *d)
{
	t_hit	hit;
	double	step = FOV / (double)SCREEN_WIDTH;
	double	start_angle = d->player.angle - FOV / 2.0 + step / 2.0;
	double	cur_angle = start_angle;
	int	x = 0;

	while (x < SCREEN_WIDTH)
	{
		get_distance(d, cur_angle, &hit);
		hit.dist *= cos(cur_angle - d->player.angle);
		hit.ray_angle = cur_angle;
		if (hit.is_vertical)
		{
			if (cos(cur_angle) > 0)
				hit.tex_id = 3;
			else
				hit.tex_id = 2;
		}
		else
		{
			if (sin(cur_angle) > 0)
				hit.tex_id = 0;
			else
				hit.tex_id = 1;
		}
		draw_wall_3d(d, x, &hit);
		cur_angle += step;
		x++;
	}
}
