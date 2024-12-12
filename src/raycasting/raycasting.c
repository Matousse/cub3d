/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 06:32:47 by dloisel           #+#    #+#             */
/*   Updated: 2024/12/12 06:33:35 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Fonction principale de raycasting avec textures */
void	raycasting(t_game *game)
{
	for (int x = 0; x < WINDOW_WIDTH; x++)
	{
		double camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

		int map_x = (int)game->player.pos_x;
		int map_y = (int)game->player.pos_y;

		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);

		double side_dist_x;
		double side_dist_y;
		int step_x;
		int step_y;
		int hit = 0;
		int side;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (game->player.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->player.pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (game->player.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game->player.pos_y) * delta_dist_y;
		}
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (game->map[map_x][map_y] > 0)
				hit = 1;
		}
		double wall_x;
		if (side == 0)
		{
			double perp_wall_dist = (map_x - game->player.pos_x + (1 - step_x) / 2) / ray_dir_x;
			wall_x = game->player.pos_y + perp_wall_dist * ray_dir_y;
		}
		else
		{
			double perp_wall_dist = (map_y - game->player.pos_y + (1 - step_y) / 2) / ray_dir_y;
			wall_x = game->player.pos_x + perp_wall_dist * ray_dir_x;
		}
		wall_x -= floor(wall_x);
		int tex_x = (int)(wall_x * TEX_WIDTH);
		if (side == 0 && ray_dir_x > 0)
			tex_x = TEX_WIDTH - tex_x - 1;
		if (side == 1 && ray_dir_y < 0)
			tex_x = TEX_WIDTH - tex_x - 1;
		double perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (map_x - game->player.pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - game->player.pos_y + (1 - step_y) / 2) / ray_dir_y;
		int line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
		int draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
		if (draw_end >= WINDOW_HEIGHT)
			draw_end = WINDOW_HEIGHT - 1;
		/* Sélection de la texture selon le côté touché */
		t_texture *texture;
		if (side == 0)
			texture = ray_dir_x > 0 ? &game->textures.east : &game->textures.west;
		else
			texture = ray_dir_y > 0 ? &game->textures.south : &game->textures.north;
		/* Dessin de la colonne texturée */
		double step = 1.0 * TEX_HEIGHT / line_height;
		double tex_pos = (draw_start - WINDOW_HEIGHT / 2 + line_height / 2) * step;

		for (int y = draw_start; y < draw_end; y++)
		{
			int tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
			tex_pos += step;
			int color = get_texture_color(texture, tex_x, tex_y);
			/* Assombrir légèrement les côtés Y */
			if (side == 1)
				color = (color >> 1) & 0x7F7F7F;
			put_pixel(game, x, y, color);
		}
		/* Dessin du sol et du plafond */
		for (int y = 0; y < draw_start; y++)
			put_pixel(game, x, y, 0x00AAAAAA); /* Plafond */
		for (int y = draw_end; y < WINDOW_HEIGHT; y++)
			put_pixel(game, x, y, 0x00555555); /* Sol */
	}
}

/* Boucle de rendu */
int render(t_game *game)
{
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
