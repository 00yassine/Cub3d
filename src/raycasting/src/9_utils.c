/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:27:33 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/29 08:37:51 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

unsigned int	rgb_to_hex(t_color *c)
{
	unsigned int	hex;

	hex = 0;
	hex |= (c->r) << 16;
	hex |= (c->g) << 8;
	hex |= (c->b);
	return (hex);
}

int	is_wall(t_data *d, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)floor(x / TS);
	map_y = (int)floor(y / TS);
	if (map_x < 0 || map_y < 0 || map_x >= d->cols || map_y >= d->rows)
		return (1);
	return (d->map[map_y][map_x] == '1');
}

void	set_vertical_hit(t_hit *hit, t_point x_int, double x_dist)
{
	hit->hit_x = x_int.x;
	hit->hit_y = x_int.y;
	hit->dist = x_dist;
	hit->is_vertical = 1;
}
