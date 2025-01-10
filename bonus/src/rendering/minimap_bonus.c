/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 00:31:19 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/11 00:23:26 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

// Fonctions pour la minimap

void	draw_direction(t_game *game, t_minimap_coords *mc)
{
	t_draw_line	dl;
	int			i;

	init_draw_line(game, mc, &dl);
	if (dl.steps <= 0)
		return ;
	i = 0;
	while (i < dl.steps)
	{
		if (dl.x >= 0 && dl.x < game->minimap->width
			&& dl.y >= 0 && dl.y < game->minimap->height)
			put_pixel_minimap(game->minimap, round(dl.x),
				round(dl.y), 0xFFFFFF);
		dl.x += dl.x_inc;
		dl.y += dl.y_inc;
		i++;
	}
}

void	process_cell(t_game *game, t_minimap_coords *mc, t_map_iter *iter)
{
	mc->map_x = floor(game->player.pos_y) + iter->x;
	mc->map_y = floor(game->player.pos_x) + iter->y;
	mc->mini_x = mc->center_x + (iter->x * mc->cell_size);
	mc->mini_y = mc->center_y + (iter->y * mc->cell_size);
	if (mc->map_x >= 0 && mc->map_x < game->map.width
		&& mc->map_y >= 0 && mc->map_y < game->map.height)
		draw_cell(game, mc);
}

void	update_map_cells(t_game *game, t_minimap_coords *mc)
{
	t_map_iter	iter;

	iter.max_x = game->minimap->width / mc->cell_size / 2;
	iter.max_y = game->minimap->height / mc->cell_size / 2;
	iter.y = -iter.max_y;
	while (iter.y <= iter.max_y)
	{
		iter.x = -iter.max_x;
		while (iter.x <= iter.max_x)
		{
			process_cell(game, mc, &iter);
			iter.x++;
		}
		iter.y++;
	}
}

void	update_minimap(t_game *game)
{
	t_minimap_coords	mc;

	if (!game->minimap)
		return ;
	mc.cell_size = 20;
	mc.center_x = game->minimap->width / 2;
	mc.center_y = game->minimap->height / 2;
	ft_memset(game->minimap->addr, 0,
		game->minimap->height * game->minimap->line_length);
	update_map_cells(game, &mc);
	draw_player(game, &mc);
	draw_direction(game, &mc);
	draw_minimap_border(game, 0, 0, 5);
}
