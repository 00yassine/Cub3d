#include "../../../includes/cub3d.h"


void	draw_player(t_data *data, char *img_adr, int line_len)
{
	int cx = (int)round(data->player.fpx);
	int cy = (int)round(data->player.fpy);
	int dx = -PLAYER_R;
	while (dx <= PLAYER_R)
	{
		int dy = -PLAYER_R;
		while (dy <= PLAYER_R)
		{
			if (dx*dx + dy*dy <= PLAYER_R*PLAYER_R)
				((unsigned int *)img_adr)[(cy + dy) * (line_len/4) + (cx + dx)] = 0xFF0000;
			dy++;
		}
		dx++;
	}
}

void	init_player_pos(t_data *data)
{
	int r = 0;
	while (r < data->rows)
	{
		int c = 0;
		while (c < data->cols)
		{
			char cell = data->map[r][c];
			if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
			{
				data->player.x = c*TS + TS/2;
				data->player.y = r*TS + TS/2;
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
