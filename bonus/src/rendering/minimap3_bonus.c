/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 02:40:56 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/10 18:39:15 by dmathis          ###   ########.fr       */
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
