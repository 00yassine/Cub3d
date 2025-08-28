#include "../../../includes/cub3d.h"

double get_distance(t_data *d, double ray_angle)
{
    double t = 0.0;
    double maxDist = hypot((double)(d->cols * TS), (double)(d->rows * TS));

    while (t < maxDist)
    {
        int px = (int)(d->player.fpx + cos(ray_angle) * t);
        int py = (int)(d->player.fpy + sin(ray_angle) * t);

        if (px < 0 || py < 0 || px >= d->cols * TS || py >= d->rows * TS)
            break;
        if (is_wall(d, px, py))
            break;
        t += 1.0;
    }
    return t;
}
