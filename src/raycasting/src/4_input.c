/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkharti <elkharti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:24:27 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/22 12:14:01 by elkharti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	key_press(int key, void *p)
{
	t_data	*d;

	d = (t_data *)p;
	if (key == 65307)
	{
		cleanup_data(d);
		exit(0);
	}
	if (key == 119)
		d->input.k_up = 1;
	if (key == 115)
		d->input.k_down = 1;
	if (key == 97)
		d->input.k_view_left = 1;
	if (key == 100)
		d->input.k_view_right = 1;
	if (key == 65361)
		d->input.k_left = 1;
	if (key == 65363)
		d->input.k_right = 1;
	if (key == 65505 || key == 65506)
		d->speed *= 2;
	return (0);
}

int	key_release(int key, void *p)
{
	t_data	*d;

	d = (t_data *)p;
	if (key == 119)
		d->input.k_up = 0;
	if (key == 115)
		d->input.k_down = 0;
	if (key == 97)
		d->input.k_view_left = 0;
	if (key == 100)
		d->input.k_view_right = 0;
	if (key == 65361)
		d->input.k_left = 0;
	if (key == 65363)
		d->input.k_right = 0;
	if (key == 65505 || key == 65506)
		d->speed = 1;
	return (0);
}

int	close_window(void *p)
{
	t_data	*data;

	data = (t_data *)p;
	cleanup_data(data);
	exit(0);
	return (0);
}

int	handle_mouse(int x, int y, void *param)
{
	t_data		*data;
	static int	prev_x = SCREEN_WIDTH / 2;
	int			delta_x;

	(void)y;
	data = (t_data *)param;
	delta_x = x - prev_x;
	if (delta_x > 0)
		data->player.angle += ROT_SPEED * 2;
	else if (delta_x < 0)
		data->player.angle -= ROT_SPEED * 2;
	if (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
	if (data->player.angle >= 2 * M_PI)
		data->player.angle -= 2 * M_PI;
	prev_x = x;
	return (0);
}
