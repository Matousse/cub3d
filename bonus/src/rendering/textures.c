/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:00:12 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/10 23:15:52 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// textures.c

#include "../../../includes/cub3d_bonus.h"

/* Fonction pour charger une texture */
int	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		return (0);
	}
	texture->data = (int *)mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
	return (1);
}

int    load_textures(t_game *game)
{
	int i;

	if (!load_texture(game, &game->textures.north, game->map.no_texture))
		return (0);
	if (!load_texture(game, &game->textures.south, game->map.so_texture))
		return (0);
	if (!load_texture(game, &game->textures.east, game->map.ea_texture))
		return (0);
	if (!load_texture(game, &game->textures.west, game->map.we_texture))
		return (0);
	if (!load_texture(game, &game->textures.door, game->map.door_texture))
		return (0);
	
	// Ajout du chargement des textures win
	for (i = 0; i < 9; i++)
	{
		if (game->map.win_textures[i])
		{
			if (!load_texture(game, &game->textures.win[i], game->map.win_textures[i]))
			{
				printf("Failed to load win texture %d\n", i + 1);
				return (0);
			}
		}
	}

	if (game->map.wallsmiley1_texture)
	{
		if (!load_texture(game, &game->textures.wallsmiley1, game->map.wallsmiley1_texture))
			printf("Failed to load smiley1\n");
	}
	if (game->map.wallsmiley2_texture)
	{
		if (!load_texture(game, &game->textures.wallsmiley2, game->map.wallsmiley2_texture))
			printf("Failed to load smiley2\n");
	}
	return (1);
}
