/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:01:52 by elkharti          #+#    #+#             */
/*   Updated: 2025/10/25 17:39:07 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_2d_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	cleanup_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->map)
		free_2d_array(data->map);
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
}

void	cleanup_map(t_map *map)
{
	if (!map)
		return ;
	if (map->no_player)
		free(map->no_player);
	if (map->so_player)
		free(map->so_player);
	if (map->we_player)
		free(map->we_player);
	if (map->ea_player)
		free(map->ea_player);
	free(map);
}
