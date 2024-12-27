/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 00:31:19 by dloisel           #+#    #+#             */
/*   Updated: 2024/12/28 00:34:46 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Fonctions pour la minimap
void init_minimap(t_game *game)
{
	game->minimap = malloc(sizeof(t_minimap));
	if (!game->minimap)
		return ;

	game->minimap->width = MINIMAP_WIDTH;
	game->minimap->height = MINIMAP_HEIGHT;
	game->minimap->img = mlx_new_image(game->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	game->minimap->addr = mlx_get_data_addr(game->minimap->img,
		&game->minimap->bits_per_pixel,
		&game->minimap->line_length,
		&game->minimap->endian);
}

static void put_pixel_minimap(t_minimap *minimap, int x, int y, int color)
{
	char    *dst;

	if (x >= 0 && x < minimap->width && y >= 0 && y < minimap->height)
	{
		dst = minimap->addr + (y * minimap->line_length + x * (minimap->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

static void apply_gaussian_blur(t_minimap *minimap)
{
	float kernel[MINIMAP_BLUR_RADIUS * 2 + 1][MINIMAP_BLUR_RADIUS * 2 + 1];
	float sigma = MINIMAP_BLUR_SIGMA;
	float sum = 0.0f;
	char *temp = malloc(minimap->height * minimap->line_length);

	if (!temp)
		return;

	// Création du kernel gaussien
	for (int y = -MINIMAP_BLUR_RADIUS; y <= MINIMAP_BLUR_RADIUS; y++)
	{
		for (int x = -MINIMAP_BLUR_RADIUS; x <= MINIMAP_BLUR_RADIUS; x++)
		{
			float value = exp(-(x * x + y * y) / (2.0f * sigma * sigma));
			kernel[y + MINIMAP_BLUR_RADIUS][x + MINIMAP_BLUR_RADIUS] = value;
			sum += value;
		}
	}

	// Normalisation du kernel
	for (int y = 0; y < MINIMAP_BLUR_RADIUS * 2 + 1; y++)
		for (int x = 0; x < MINIMAP_BLUR_RADIUS * 2 + 1; x++)
			kernel[y][x] /= sum;

	memcpy(temp, minimap->addr, minimap->height * minimap->line_length);

	// Application du flou
	for (int y = MINIMAP_BLUR_RADIUS; y < minimap->height - MINIMAP_BLUR_RADIUS; y++)
	{
		for (int x = MINIMAP_BLUR_RADIUS; x < minimap->width - MINIMAP_BLUR_RADIUS; x++)
		{
			float r = 0, g = 0, b = 0;
			for (int ky = -MINIMAP_BLUR_RADIUS; ky <= MINIMAP_BLUR_RADIUS; ky++)
			{
				for (int kx = -MINIMAP_BLUR_RADIUS; kx <= MINIMAP_BLUR_RADIUS; kx++)
				{
					int px = x + kx;
					int py = y + ky;
					int pixel_pos = py * minimap->line_length + px * (minimap->bits_per_pixel / 8);
					float k = kernel[ky + MINIMAP_BLUR_RADIUS][kx + MINIMAP_BLUR_RADIUS];

					b += (unsigned char)temp[pixel_pos] * k;
					g += (unsigned char)temp[pixel_pos + 1] * k;
					r += (unsigned char)temp[pixel_pos + 2] * k;
				}
			}
			put_pixel_minimap(minimap, x, y, ((int)r << 16) | ((int)g << 8) | (int)b);
		}
	}
	free(temp);
}

void update_minimap(t_game *game)
{
	if (!game->minimap)
		return;

	// Taille d'une cellule de la minimap
	int cell_size = 20;  // Taille fixe pour chaque cellule

	// Effacer la minimap
	ft_memset(game->minimap->addr, 0,
		game->minimap->height * game->minimap->line_length);

	// Position centrale de la minimap
	int center_x = game->minimap->width / 2;
	int center_y = game->minimap->height / 2;

	// Nombre de cellules visibles
	int cells_x = game->minimap->width / cell_size;
	int cells_y = game->minimap->height / cell_size;

	// Pour chaque cellule visible dans la minimap
	for (int y = -cells_y/2; y <= cells_y/2; y++)
	{
		for (int x = -cells_x/2; x <= cells_x/2; x++)
		{
			// Calculer la position dans la map du jeu
			int map_x = floor(game->player.pos_y) + x;
			int map_y = floor(game->player.pos_x) + y;

			// Position dans la minimap
			int mini_x = center_x + (x * cell_size);
			int mini_y = center_y + (y * cell_size);

			// Vérifier si la position est dans les limites de la map
			if (map_x >= 0 && map_x < game->map.width &&
				map_y >= 0 && map_y < game->map.height)
			{
				int color;
				if (game->map.fullmap[map_y][map_x] == '1')
					color = 0xFFFFFF;  // Murs en blanc
				else if (game->map.fullmap[map_y][map_x] == '0' ||
						game->map.fullmap[map_y][map_x] == 'N' ||
						game->map.fullmap[map_y][map_x] == 'S' ||
						game->map.fullmap[map_y][map_x] == 'E' ||
						game->map.fullmap[map_y][map_x] == 'W')
					color = 0x444444;  // Sol en gris
				else
					color = 0x000000;  // Vide en noir

				// Dessiner la cellule avec une bordure
				for (int py = 0; py < cell_size; py++)
				{
					for (int px = 0; px < cell_size; px++)
					{
						int draw_x = mini_x - (cell_size / 2) + px;
						int draw_y = mini_y - (cell_size / 2) + py;
						if (draw_x >= 0 && draw_x < game->minimap->width &&
							draw_y >= 0 && draw_y < game->minimap->height)
						{
							// Ajouter une bordure d'un pixel
							if (px == 0 || px == cell_size-1 || py == 0 || py == cell_size-1)
								put_pixel_minimap(game->minimap, draw_x, draw_y, 0x333333);
							else
								put_pixel_minimap(game->minimap, draw_x, draw_y, color);
						}
					}
				}
			}
		}
	}

	// Dessiner le joueur au centre exact
	int player_size = 4;

	for (int py = -player_size; py <= player_size; py++)
	{
		for (int px = -player_size; px <= player_size; px++)
		{
			if (px * px + py * py <= player_size * player_size)
			{
				put_pixel_minimap(game->minimap,
					center_x + px,
					center_y + py,
					0xFF0000);
			}
		}
	}

	// Direction du joueur
	int dir_x = (center_x + game->player.dir_y * cell_size);
	int dir_y = (center_y + game->player.dir_x * cell_size);

	// Tracer la ligne de direction
	int dx = dir_x - center_x;
	int dy = dir_y - center_y;
	int steps = sqrt(dx * dx + dy * dy);

	if (steps > 0)
	{
		double x_inc = dx / (double)steps;
		double y_inc = dy / (double)steps;
		double x = center_x;
		double y = center_y;

		for (int i = 0; i < steps; i++)
		{
			if (x >= 0 && x < game->minimap->width &&
				y >= 0 && y < game->minimap->height)
			{
				put_pixel_minimap(game->minimap, round(x), round(y), 0xFF0000);
			}
			x += x_inc;
			y += y_inc;
		}
	}
}
