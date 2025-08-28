#include "../../../includes/cub3d.h"

int	key_press(int key, void *p)
{
	t_data *d = (t_data*)p;
	if (key == 65307) exit(0);
	if (key == 65362) d->input.k_up = 1;
	if (key == 65364) d->input.k_down = 1;
	if (key == 65361) d->input.k_left = 1;
	if (key == 65363) d->input.k_right = 1;
	return 0;
}

int	key_release(int key, void *p)
{
	t_data *d = (t_data*)p;
	if (key == 65362) d->input.k_up = 0;
	if (key == 65364) d->input.k_down = 0;
	if (key == 65361) d->input.k_left = 0;
	if (key == 65363) d->input.k_right = 0;
	return 0;
}
