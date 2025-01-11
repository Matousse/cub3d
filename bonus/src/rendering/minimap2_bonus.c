/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 02:40:31 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/11 02:53:29 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

int	get_cell_color(char cell_type)
{
	if (cell_type == '1' || cell_type == 'T')
		return (0x9c0c0b);
	if (cell_type == '0' || cell_type == 'N' || cell_type == 'S'
		|| cell_type == 'E' || cell_type == 'W')
		return (0xc28805);
	if (cell_type == 'D')
		return (0x3d87cf);
	return (0x000000);
}

void	init_minimap(t_game *game)
{
	game->minimap = malloc(sizeof(t_minimap));
	if (!game->minimap)
		return ;
	game->minimap->width = MINIMAP_WIDTH;
	game->minimap->height = MINIMAP_HEIGHT;
	game->minimap->img = mlx_new_image(game->mlx, MINIMAP_WIDTH, \
	MINIMAP_HEIGHT);
	game->minimap->addr = mlx_get_data_addr(game->minimap->img,
			&game->minimap->bits_per_pixel,
			&game->minimap->line_length,
			&game->minimap->endian);
}

void	put_pixel_minimap(t_minimap *minimap, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < minimap->width && y >= 0 && y < minimap->height)
	{
		dst = minimap->addr + (y * minimap->line_length + x * \
		(minimap->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_cell_pixels(t_game *game, t_minimap_coords *mc, int px, int py)
{
	int	draw_x;
	int	draw_y;
	int	color;

	draw_x = mc->mini_x - (mc->cell_size / 2) + px;
	draw_y = mc->mini_y - (mc->cell_size / 2) + py;
	if (draw_x >= 0 && draw_x < game->minimap->width
		&& draw_y >= 0 && draw_y < game->minimap->height
		&& mc->map_y >= 0 && mc->map_y < game->map.height
		&& mc->map_x >= 0
		&& mc->map_x < (int)ft_strlen(game->map.fullmap[mc->map_y]))
	{
		color = get_cell_color(game->map.fullmap[mc->map_y][mc->map_x]);
		if (px == 0 || px == mc->cell_size - 1
			|| py == 0 || py == mc->cell_size - 1)
			put_pixel_minimap(game->minimap, draw_x, draw_y, 0x333333);
		else
			put_pixel_minimap(game->minimap, draw_x, draw_y, color);
	}
}
