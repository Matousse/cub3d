/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 02:40:56 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/11 00:23:33 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	draw_cell(t_game *game, t_minimap_coords *mc)
{
	int	px;
	int	py;

	py = 0;
	while (py < mc->cell_size)
	{
		px = 0;
		while (px < mc->cell_size)
		{
			draw_cell_pixels(game, mc, px, py);
			px++;
		}
		py++;
	}
}

void	draw_player(t_game *game, t_minimap_coords *mc)
{
	int	px;
	int	py;
	int	size;

	size = 4;
	py = -size;
	while (py <= size)
	{
		px = -size;
		while (px <= size)
		{
			if (px * px + py * py <= size * size)
				put_pixel_minimap(game->minimap,
					mc->center_x + px, mc->center_y + py, 0xFFFFFF);
			px++;
		}
		py++;
	}
}

void	init_draw_line(t_game *game, t_minimap_coords *mc, t_draw_line *dl)
{
	dl->dir_x = (mc->center_x + game->player.dir_y * mc->cell_size);
	dl->dir_y = (mc->center_y + game->player.dir_x * mc->cell_size);
	dl->x = mc->center_x;
	dl->y = mc->center_y;
	dl->steps = sqrt(pow(dl->dir_x - mc->center_x, 2)
			+ pow(dl->dir_y - mc->center_y, 2));
	if (dl->steps > 0)
	{
		dl->x_inc = (dl->dir_x - mc->center_x) / (double)dl->steps;
		dl->y_inc = (dl->dir_y - mc->center_y) / (double)dl->steps;
	}
}

void	draw_minimap_border(t_game *game, int x, int y, int border_thickness)
{
	while (y < border_thickness)
	{
		x = 0;
		while (x < game->minimap->width)
		{
			put_pixel_minimap(game->minimap, x, y, 0x9c0c0b);
			put_pixel_minimap(game->minimap, x, \
			game->minimap->height - 1 - y, 0x9c0c0b);
			x++;
		}
		y++;
	}
	x = 0;
	while (x < border_thickness)
	{
		y = 0;
		while (y < game->minimap->height)
		{
			put_pixel_minimap(game->minimap, x, y, 0x9c0c0b);
			put_pixel_minimap(game->minimap, \
			game->minimap->width - 1 - x, y, 0x9c0c0b);
			y++;
		}
		x++;
	}
}
