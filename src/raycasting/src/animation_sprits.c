#include "../../../includes/cub3d.h"

void	load_animation(t_anime *d)
{
	int w;
	int h;

	d->frames[0] = mlx_xpm_file_to_image(d->mlx, "textures/fire_0.xpm", &w, &h);
	d->frames[1] = mlx_xpm_file_to_image(d->mlx, "textures/fire_1.xpm", &w, &h);
	d->frames[2] = mlx_xpm_file_to_image(d->mlx, "textures/fire_2.xpm", &w, &h);
	d->frames[3] = mlx_xpm_file_to_image(d->mlx, "textures/fire_3.xpm", &w, &h);

	for (int i = 0; i < 4; i++)
	{
		if (!d->frames[i])
		{
			printf("Failed to load frame %d\n", i);
			exit(1);
		}
	}
	d->current_frame = 0;
	d->frame_delay = 0;
}

int	render_next_frame(t_anime *d)
{
	mlx_clear_window(d->mlx, d->win);
	d->frame_delay++;
	if (d->frame_delay >= 7)
	{
		d->current_frame = (d->current_frame + 1) % 4;
		d->frame_delay = 0;
	}
	int x = (WIDTH / 2) - 64;
	int y = (HEIGHT / 2) - 64;
	mlx_put_image_to_window(d->mlx, d->win, d->frames[d->current_frame], x, y);

	return (0);
}
