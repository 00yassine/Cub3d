/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   2_draw_2D_map.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ykabili- <ykabili-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/10/15 11:38:32 by ykabili-		  #+#	#+#			 */
/*   Updated: 2025/10/15 12:14:29 by ykabili-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

#define MINIMAP_SIZE		200
#define PLAYER_SIZE			4
#define MINIMAP_OFFSET_X	10
#define MINIMAP_OFFSET_Y	10
#define TILE_SIZE			64
#define SCALE_FACTOR		8.0

void	my_mlx_pixel_put_minimap(t_data *d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return ;
	dst = d->img_adr + (y * d->line_len + x * (d->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	draw_square(t_data *d, t_draw_minimap *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->cell)
	{
		j = 0;
		while (j < m->cell)
		{
			my_mlx_pixel_put_minimap(d,
				(int)(m->tile_x + j),
				(int)(m->tile_y + i),
				m->color);
			j++;
		}
		i++;
	}
}

static void	draw_player_dir(t_data *d)
{
	t_draw_dir	r;

	r.dir_len = 15.0;
	r.start_x = MINIMAP_OFFSET_X + MINIMAP_SIZE / 2;
	r.start_y = MINIMAP_OFFSET_Y + MINIMAP_SIZE / 2;
	r.end_x = r.start_x + cos(d->player.angle) * r.dir_len;
	r.end_y = r.start_y + sin(d->player.angle) * r.dir_len;
	r.dx = r.end_x - r.start_x;
	r.dy = r.end_y - r.start_y;
	if (fabs(r.dx) > fabs(r.dy))
		r.steps = fabs(r.dx);
	else
		r.steps = fabs(r.dy);
	r.x_inc = r.dx / r.steps;
	r.y_inc = r.dy / r.steps;
	r.i = 0;
	while (r.i <= r.steps)
	{
		my_mlx_pixel_put_minimap(d, (int)r.start_x, (int)r.start_y, 0x00FF00);
		r.start_x += r.x_inc;
		r.start_y += r.y_inc;
		r.i++;
	}
}

static void	draw_minimap_cell(t_data *d, t_draw_minimap *m)
{
	if (m->tile_x + m->cell < MINIMAP_OFFSET_X
		|| m->tile_y + m->cell < MINIMAP_OFFSET_Y
		|| m->tile_x > MINIMAP_OFFSET_X + MINIMAP_SIZE
		|| m->tile_y > MINIMAP_OFFSET_Y + MINIMAP_SIZE)
		return ;
	if (d->map[m->y][m->x] == '1')
		m->color = 0xFAB12F;
	else
		m->color = 0x5C3E94;
	draw_square(d, m);
}

void	draw_minimap(t_data *d)
{
	t_draw_minimap	mini;

	mini.cell = TILE_SIZE / SCALE_FACTOR;
	mini.player_x = d->player.fpx;
	mini.player_y = d->player.fpy;
	mini.y = -1;
	while (++mini.y < d->rows)
	{
		mini.x = -1;
		while (++mini.x < d->cols)
		{
			mini.map_x = mini.x * TILE_SIZE;
			mini.map_y = mini.y * TILE_SIZE;
			mini.tile_x = (mini.map_x - mini.player_x) / SCALE_FACTOR
				+ MINIMAP_OFFSET_X + MINIMAP_SIZE / 2;
			mini.tile_y = (mini.map_y - mini.player_y) / SCALE_FACTOR
				+ MINIMAP_OFFSET_Y + MINIMAP_SIZE / 2;
			draw_minimap_cell(d, &mini);
		}
	}
	draw_player_mini(d);
	draw_player_dir(d);
}
