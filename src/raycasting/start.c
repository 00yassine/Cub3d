/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:22:00 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/14 10:22:21 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	start(t_map *map_data)
{
	t_data	d;

	init_data_from_map(&d, map_data);
	mlx_loop(d.mlx_ptr);
	return (0);
}
