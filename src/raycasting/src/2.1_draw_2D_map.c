/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.1_draw_2D_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:57:53 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/15 11:57:54 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

#define MINIMAP_SIZE		200
#define PLAYER_SIZE			4
#define MINIMAP_OFFSET_X	10
#define MINIMAP_OFFSET_Y	10

void	draw_player_mini(t_data *d)
{
	int	i;
	int	j;
	int	cx;
	int	cy;

	cx = MINIMAP_OFFSET_X + MINIMAP_SIZE / 2 - PLAYER_SIZE / 2;
	cy = MINIMAP_OFFSET_Y + MINIMAP_SIZE / 2 - PLAYER_SIZE / 2;
	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			my_mlx_pixel_put_minimap(d, cx + j, cy + i, 0xFBF3D1);
			j++;
		}
		i++;
	}
}
