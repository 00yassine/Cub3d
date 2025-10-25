/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_1_draw_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 09:20:00 by elkharti          #+#    #+#             */
/*   Updated: 2025/10/25 09:16:04 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *d, int x, int y, int color)
{
	char	*dst;

	dst = d->img_adr + (y * d->line_len + x * (d->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_wall_params(t_data *d, t_hit *hit, t_wall *w)
{
	w->line_height = (int)((TS * SCREEN_HEIGHT) / hit->dist);
	w->draw_start = (SCREEN_HEIGHT / 2) - (w->line_height / 2);
	if (w->draw_start < 0)
		w->draw_start = 0;
	w->draw_end = (SCREEN_HEIGHT / 2) + (w->line_height / 2);
	if (w->draw_end >= SCREEN_HEIGHT)
		w->draw_end = SCREEN_HEIGHT - 1;
	w->tex = &d->tex[hit->tex_id];
}

void	calc_texture_x(t_hit *hit, t_wall *w)
{
	if (hit->is_vertical)
		w->tex_x = (int)fmod(hit->hit_y, TS) * w->tex->width / TS;
	else
		w->tex_x = (int)fmod(hit->hit_x, TS) * w->tex->width / TS;
	if ((hit->is_vertical && cos(hit->ray_angle) < 0)
		|| (!hit->is_vertical && sin(hit->ray_angle) > 0))
		w->tex_x = w->tex->width - w->tex_x - 1;
}

void	draw_ceiling_floor(t_data *d, int x, t_wall *w)
{
	int	y;

	y = 0;
	while (y < w->draw_start)
	{
		my_mlx_pixel_put(d, x, y, rgb_to_hex(&d->ceiling));
		y++;
	}
	y = w->draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(d, x, y, rgb_to_hex(&d->floor));
		y++;
	}
}

void	draw_textured_wall(t_data *d, int x, t_wall *w)
{
	int		y;
	int		color;
	double	step;
	double	tex_pos;

	step = (double)w->tex->height / w->line_height;
	tex_pos = (w->draw_start - SCREEN_HEIGHT / 2 + w->line_height / 2) * step;
	y = w->draw_start;
	while (y <= w->draw_end)
	{
		color = *(unsigned int *)(w->tex->addr + ((int)tex_pos % w->tex->height)
				* w->tex->line_len + w->tex_x * (w->tex->bpp / 8));
		my_mlx_pixel_put(d, x, y, color);
		tex_pos += step;
		y++;
	}
}
