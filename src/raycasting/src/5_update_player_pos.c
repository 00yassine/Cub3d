/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_update_player_pos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykabili- <ykabili-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:36:35 by ykabili-          #+#    #+#             */
/*   Updated: 2025/10/14 13:28:30 by ykabili-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	clear_img(t_data *d)
{
	ft_memset(d->img_adr, 0, SCREEN_HEIGHT * d->line_len);
}

static void	move(t_data *d, double angle)
{
	double	new_x;
	double	new_y;
	double	offset_x;
	double	offset_y;

	new_x = d->player.fpx + cos(angle) * MOVE_SPEED * d->speed;
	new_y = d->player.fpy + sin(angle) * MOVE_SPEED * d->speed;
	offset_x = 5;
	if (cos(angle) < 0)
		offset_x = -5;
	offset_y = 5;
	if (sin(angle) < 0)
		offset_y = -5;
	if (!is_wall(d, new_x + offset_x, d->player.fpy))
		d->player.fpx = new_x;
	if (!is_wall(d, d->player.fpx, new_y + offset_y))
		d->player.fpy = new_y;
	d->player.x = (int)round(d->player.fpx);
	d->player.y = (int)round(d->player.fpy);
}

static void	handle_movement(t_data *d)
{
	if (d->input.k_up == 1)
		move(d, d->player.angle);
	if (d->input.k_down == 1)
		move(d, d->player.angle + M_PI);
	if (d->input.k_view_left == 1)
		move(d, d->player.angle - M_PI / 2);
	if (d->input.k_view_right == 1)
		move(d, d->player.angle + M_PI / 2);
}

static void	handle_rotation(t_data *d)
{
	int	dir;

	dir = 0;
	if (d->input.k_right)
		dir++;
	if (d->input.k_left)
		dir--;
	if (!dir)
		return ;
	d->player.angle += ROT_SPEED * dir;
	if (d->player.angle >= 2 * M_PI)
		d->player.angle -= 2 * M_PI;
	else if (d->player.angle < 0)
		d->player.angle += 2 * M_PI;
}

int	update_loop(void *p)
{
	t_data	*d;

	d = (t_data *)p;
	handle_movement(d);
	handle_rotation(d);
	clear_img(d);
	draw_3d(d);
	draw_minimap(d);
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img, 0, 0);
	return (0);
}
