#include "../../../includes/cub3d.h"

#define MINIMAP_RANGE 6
#define MINIMAP_CELL  10
#define PLAYER_SIZE   8
#define MINIMAP_X     16   // top-left corner of the minimap on screen
#define MINIMAP_Y     16

void	my_mlx_pixel_put_minimap(t_data *d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return;

	dst = d->img_adr + (y * d->line_len + x * (d->bpp / 8));
	*(unsigned int *)dst = mlx_get_color_value(d->mlx_ptr, color);
}

void draw_minimap(t_data *d)
{
    if (!d->map || d->rows <= 0 || d->cols <= 0) return;

    int x, y, i, j, color;

    int start_row = (int)(d->player.fpy) - MINIMAP_RANGE;
    int end_row   = (int)(d->player.fpy) + MINIMAP_RANGE;
    int start_col = (int)(d->player.fpx) - MINIMAP_RANGE;
    int end_col   = (int)(d->player.fpx) + MINIMAP_RANGE;

    if (start_row < 0) start_row = 0;
    if (start_col < 0) start_col = 0;
    if (end_row >= d->rows) end_row = d->rows - 1;
    if (end_col >= d->cols) end_col = d->cols - 1;

    int vis_rows = end_row - start_row + 1;
    int vis_cols = end_col - start_col + 1;

    // Draw background panel so cells are visible over the scene
    int bg_w = vis_cols * MINIMAP_CELL;
    int bg_h = vis_rows * MINIMAP_CELL;
    for (y = 0; y < bg_h; y++) {
        for (x = 0; x < bg_w; x++) {
            my_mlx_pixel_put_minimap(d, MINIMAP_X + x, MINIMAP_Y + y, 0x101010);
        }
    }

    // Draw cells
    for (y = start_row; y <= end_row; y++)
    {
        for (x = start_col; x <= end_col; x++)
        {
            char c = d->map[y][x];
            if (c == '1')       color = 0x666666;  // wall
            else if (c == '0')  color = 0xBEBEBE;  // floor
            else                color = 0x808080;  // other (door/space)

            for (i = 0; i < MINIMAP_CELL; i++) {
                for (j = 0; j < MINIMAP_CELL; j++) {
                    my_mlx_pixel_put_minimap(
                        d,
                        MINIMAP_X + (x - start_col) * MINIMAP_CELL + i,
                        MINIMAP_Y + (y - start_row) * MINIMAP_CELL + j,
                        color
                    );
                }
            }
        }
    }

    // Draw player on top
    int px = MINIMAP_X + (int)((d->player.fpx - start_col) * MINIMAP_CELL) - PLAYER_SIZE / 2;
    int py = MINIMAP_Y + (int)((d->player.fpy - start_row) * MINIMAP_CELL) - PLAYER_SIZE / 2;

    for (i = 0; i < PLAYER_SIZE; i++) {
        for (j = 0; j < PLAYER_SIZE; j++) {
            my_mlx_pixel_put_minimap(d, px + i, py + j, 0xFF0000);
        }
    }
}
