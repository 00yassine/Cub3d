#include "../../../includes/cub3d.h"

static void	clear_img(t_data *d)
{
	ft_memset(d->img_data, 0, d->rows * TS * d->line_len);
}

static void	handle_movement(t_data *d)
{
	int dir = 0;

	if (d->input.k_up)
		dir++;
	if (d->input.k_down)
		dir--;
	if (!dir)
		return;

	double new_x = d->player.fpx + cos(d->player.angle) * MOVE_SPEED * dir;
	double new_y = d->player.fpy + sin(d->player.angle) * MOVE_SPEED * dir;

	if (can_move(d, (int)new_x, (int)d->player.fpy, PLAYER_R))
		d->player.fpx = new_x;
	if (can_move(d, (int)d->player.fpx, (int)new_y, PLAYER_R))
		d->player.fpy = new_y;
}

static void	handle_rotation(t_data *d)
{
	int dir = 0;

	if (d->input.k_right)
		dir++;
	if (d->input.k_left)
		dir--;
	if (!dir)
		return;
	d->player.angle += ROT_SPEED * dir;
	if (d->player.angle >= 2 * M_PI)
		d->player.angle -= 2 * M_PI;
	else if (d->player.angle < 0)
		d->player.angle += 2 * M_PI;

}

int update_loop(void *p)
{
	t_data *d = (t_data*)p;

	handle_movement(d);
	handle_rotation(d);
	d->player.x = (int)(d->player.fpx + 0.5);
	d->player.y = (int)(d->player.fpy + 0.5);
	clear_img(d);
	draw_2d_map(d, d->img_data, d->line_len);
	draw_player(d, d->img_data, d->line_len);
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img, 0, 0);

	return (0);
}
