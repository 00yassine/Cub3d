#include "../../../includes/cub3d.h"

static t_point	get_horizontal_intercept(double x, double y, double ray_angle)
{
	t_point	intercept;
	int		tile_y;
	double	t;

	tile_y = (int)floor(y / TS);
	if (sin(ray_angle) > 0)
		intercept.y = tile_y * TS + TS;
	else
		intercept.y = tile_y * TS;
	t = tan(ray_angle);
	if (fabs(t) < 1e-9)
		intercept.x = x;
	else
		intercept.x = x + (intercept.y - y) / t;
	return (intercept);
}

static t_point	get_vertical_intercept(double x, double y, double ray_angle)
{
	t_point	intercept;
	int		tile_x;
	double	t;

	tile_x = (int)floor(x / TS);
	if (cos(ray_angle) > 0)
		intercept.x = tile_x * TS + TS;
	else
		intercept.x = tile_x * TS;
	t = tan(ray_angle);
	if (fabs(cos(ray_angle)) < 1e-9)
		intercept.y = y;
	else
		intercept.y = y + (intercept.x - x) * t;
	return (intercept);
}

t_point get_next_intercept(t_point current, double ray_angle, int vertical)
{
    t_point next;
    double step_y;
    double step_x;
    if (!vertical)
    {
        if (sin(ray_angle) > 0)
            step_y = TS;
        else
            step_y = -TS;
        if (fabs(tan(ray_angle)) < 1e-9)
            step_x = 0;
        else
            step_x =  step_y / tan(ray_angle);
        next.x = current.x + step_x;
        next.y = current.y + step_y;
    }
    else
    {
        if (cos(ray_angle) > 0)
            step_x = TS;
        else
            step_x = -TS;
        if (fabs(tan(ray_angle)) < 1e-9)
            step_y = 0;
        else
            step_y = step_x * tan(ray_angle);
        next.x = current.x + step_x;
        next.y = current.y + step_y;
    }
    return next;
}

void get_distance(t_data *d, double ray_angle, t_hit *hit)
{
    t_point y_int;
    t_point x_int;
    double y_dist;
    double x_dist;

    y_int = get_horizontal_intercept(d->player.fpx, d->player.fpy, ray_angle);
    x_int = get_vertical_intercept(d->player.fpx, d->player.fpy, ray_angle);
    while (!is_wall(d, y_int.x, y_int.y + ((sin(ray_angle) > 0)
        * EPS - (sin(ray_angle) <= 0) * EPS)))
        y_int = get_next_intercept(y_int, ray_angle, 0);
    while (!is_wall(d, x_int.x + ((cos(ray_angle) > 0)
        * EPS - (cos(ray_angle) <= 0) * EPS), x_int.y))
        x_int = get_next_intercept(x_int, ray_angle, 1);
    y_dist = hypot(y_int.x - d->player.fpx, y_int.y - d->player.fpy);
    x_dist = hypot(x_int.x - d->player.fpx, x_int.y - d->player.fpy);
    if (y_dist < x_dist)
    {
        hit->hit_x = y_int.x, hit->hit_y = y_int.y;
        hit->dist = y_dist, hit->is_vertical = 0;
    }
    else
    {
        hit->hit_x = x_int.x, hit->hit_y = x_int.y;
        hit->dist = x_dist, hit->is_vertical = 1;
    }
}
