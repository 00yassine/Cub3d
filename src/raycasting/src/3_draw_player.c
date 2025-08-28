#include "../../../includes/cub3d.h"

void	 draw_FOV_rays(t_data *d);
void	 draw_wall_3d(t_data *d, int x, double perp_dist);


void	draw_angle_player(t_data *data)
{
	draw_FOV_rays(data);
}
void	draw_player(t_data *data, char *img_data, int line_len)
{
	int cx = data->player.x;
	int cy = data->player.y;
	int dx = -PLAYER_R;
	while (dx <= PLAYER_R)
	{ 
		int dy = -PLAYER_R;
		while (dy <= PLAYER_R)
		{
			if (dx*dx + dy*dy <= PLAYER_R*PLAYER_R)
				((unsigned int *)img_data)[(cy + dy) * (line_len/4) + (cx + dx)] = 0xFF0000;
			dy++;
		}
		dx++;
	}
	draw_angle_player(data);
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

void	draw_FOV_rays(t_data *d)
{

}

void	 draw_wall_3d(t_data *d, int x, double dist)
{

}
