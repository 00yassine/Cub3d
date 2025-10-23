/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_draw_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:44:59 by elkharti          #+#    #+#             */
/*   Updated: 2025/10/22 08:50:52 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	set_player_angle(t_data *data, char cell)
{
	if (cell == 'N')
		data->player.angle = 3.0 * M_PI / 2.0;
	else if (cell == 'S')
		data->player.angle = M_PI / 2.0;
	else if (cell == 'E')
		data->player.angle = 0.0;
	else if (cell == 'W')
		data->player.angle = M_PI;
}

static void	set_player_position(t_data *data, int r, int c, char cell)
{
	data->player.x = c * TS + TS / 2;
	data->player.y = r * TS + TS / 2;
	data->player.fpx = data->player.x;
	data->player.fpy = data->player.y;
	set_player_angle(data, cell);
}

void	init_player_pos(t_data *data)
{
	int		r;
	int		c;
	char	cell;

	r = 0;
	while (r < data->rows)
	{
		c = 0;
		while (c < data->cols && data->map[r][c]
				!= '\0' && data->map[r][c] != '\n')
		{
			cell = data->map[r][c];
			if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
			{
				set_player_position(data, r, c, cell);
				return ;
			}
			c++;
		}
		r++;
	}
}
