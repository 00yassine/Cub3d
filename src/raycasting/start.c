#include "../../includes/cub3d.h"

int	start(t_map *map_data)
{
	t_data d;

	init_data_from_map(&d, map_data);
	mlx_loop_hook(d.mlx_ptr, render_frame, &d);
	mlx_loop(d.mlx_ptr);
	return (0);
}
