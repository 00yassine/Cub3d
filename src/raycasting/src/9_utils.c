#include "../../../includes/cub3d.h"

unsigned int rgb_to_hex(t_color *c)
{
    unsigned int hex;

    hex = 0;
    hex |= (c->r) << 16;
    hex |= (c->g) << 8;
    hex |= (c->b);
    return hex;
}
int	is_wall(t_data *d, double x, double y)
{
	int map_x;
	int map_y;

	map_x = (int)floor(x / TS);
	map_y = (int)floor(y / TS);
	if (map_x < 0 || map_y < 0 || map_x >= d->cols || map_y >= d->rows)
		return (1);
	return (d->map[map_y][map_x] == '1');
}