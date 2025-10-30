/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_entry.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:22:00 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/30 08:37:45 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	raycasting_entry(t_map *map_data)
{
	t_data	d;

	init_data_from_map(&d, map_data);
	mlx_loop(d.mlx_ptr);
	return (0);
}
