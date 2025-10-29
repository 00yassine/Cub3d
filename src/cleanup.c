/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:01:52 by elkharti          #+#    #+#             */
/*   Updated: 2025/10/29 08:44:24 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void free_2d_array(char **arr)
{
	(void)arr;
	return;
}

void cleanup_data(t_data *data)
{
	int i;

	if (!data)
		return;
	if (data->mlx_ptr)
	{
		i = 0;
		while (i < 4)
		{
			if (data->tex[i].img)
				mlx_destroy_image(data->mlx_ptr, data->tex[i].img);
			i++;
		}
		if (data->img)
			mlx_destroy_image(data->mlx_ptr, data->img);
		if (data->win_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	gc_malloc(0, 0);
}

void cleanup_map(t_map *map)
{
	(void)map;
	return;
}
