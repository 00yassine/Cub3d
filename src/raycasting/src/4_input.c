#include "../../../includes/cub3d.h"

int	key_press(int key, void *p)
{
	t_data *d = (t_data*)p;
	if (key == 65307) exit(0);
	if (key == 119) d->input.k_up = 1;
	if (key == 115) d->input.k_down = 1;
	if (key == 97)  d->input.k_view_left = 1;
	if (key == 100) d->input.k_view_right = 1;
	if (key == 65361) d->input.k_left = 1;
	if (key == 65363) d->input.k_right = 1;
	if (key == 65505 || key == 65506)
    d->speed *= 2;
	return 0;
}

int	key_release(int key, void *p)
{
	t_data *d = (t_data*)p;
	if (key == 119) d->input.k_up = 0;
	if (key == 115) d->input.k_down = 0;
	if (key == 97)  d->input.k_view_left = 0;
	if (key == 100) d->input.k_view_right = 0;
	if (key == 65361) d->input.k_left = 0;
	if (key == 65363) d->input.k_right = 0;
	if (key == 65505 || key == 65506)
    d->speed = 1; 
	return 0;
}

int	close_window(void *p)
{
	(void)p;
	exit(0);
	return (0);
}

int	mouse_move(int x, int y, void *p)
{
    t_data *d = (t_data*)p;
    static int last_x = -1;
    int delta_x;

    (void)y;
    if (last_x == -1)
        last_x = x;
    delta_x = x - last_x;
    d->player.angle += delta_x * 0.0001;
    last_x = SCREEN_WIDTH / 2;
    mlx_mouse_move(d->mlx_ptr, d->win_ptr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    return (0);
}
