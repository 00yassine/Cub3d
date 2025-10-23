/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_draw_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:29:42 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/22 12:06:00 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	draw_wall_3d(t_data *d, int x, t_hit *hit)
{
	t_wall	w;

	if (hit->dist < EPS)
		hit->dist = EPS;
	init_wall_params(d, hit, &w);
	draw_ceiling_floor(d, x, &w);
	calc_texture_x(hit, &w);
	draw_textured_wall(d, x, &w);
}

static void	set_texture_id(t_hit *hit, double cur_angle)
{
	if (hit->is_vertical)
	{
		if (cos(cur_angle) > 0)
			hit->tex_id = 3;
		else
			hit->tex_id = 2;
	}
	else
	{
		if (sin(cur_angle) > 0)
			hit->tex_id = 0;
		else
			hit->tex_id = 1;
	}
}

static void	init_ray_params(t_data *d, double *step,
							double *start, double *cur)
{
	*step = FOV / (double)SCREEN_WIDTH;
	*start = d->player.angle - FOV / 2.0 + *step / 2.0;
	*cur = *start;
}

void	draw_3d(t_data *d, int x)
{
	t_hit	hit;
	double	step;
	double	start_angle;
	double	cur_angle;

	init_ray_params(d, &step, &start_angle, &cur_angle);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		get_distance(d, cur_angle, &hit);
		hit.dist *= cos(cur_angle - d->player.angle);
		hit.ray_angle = cur_angle;
		set_texture_id(&hit, cur_angle);
		draw_wall_3d(d, x, &hit);
		cur_angle += step;
		x++;
	}
}
