#include "../../../includes/cub3d.h"

void init_player_pos(t_data *data)
{
	int	r;

	r = 0;
	while (r < data->rows)
	{
		int c = 0;
		while (c < data->cols && data->map[r][c] != '\0' && data->map[r][c] != '\n')
		{
			char cell = data->map[r][c];
			if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
			{
				data->player.x = c * TS + TS / 2;
				data->player.y = r * TS + TS / 2;
				data->player.fpx = data->player.x;
				data->player.fpy = data->player.y;
				if (cell == 'N')
					data->player.angle = 3.0 * M_PI / 2.0;
				else if (cell == 'S')
					data->player.angle = M_PI / 2.0;
				else if (cell == 'E')
					data->player.angle = 0.0;
				else if (cell == 'W')
					data->player.angle = M_PI;
				return;
			}
			c++;
		}
		r++;
	}
}
