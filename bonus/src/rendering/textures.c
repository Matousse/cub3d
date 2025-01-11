/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:00:12 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/11 02:33:46 by dmathis          ###   ########.fr       */
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

int	load_textures3(t_game *game)
{
	if (game->map.wallsmiley1_texture)
		if (!load_texture(game, &game->textures.wallsmiley1,
				game->map.wallsmiley1_texture))
			ft_error_handling(game, "Failed to load smiley1");
	if (game->map.wallsmiley2_texture)
		if (!load_texture(game, &game->textures.wallsmiley2,
				game->map.wallsmiley2_texture))
			ft_error_handling(game, "Failed to load smiley2");
	return (1);
}

int	load_textures2(t_game *game)
{
	if (game->map.win_textures[0] && !load_texture(game, &game->textures.win[0],
			game->map.win_textures[0]))
		ft_error_handling(game, "Failed to load win texture 1");
	if (game->map.win_textures[1] && !load_texture(game, &game->textures.win[1],
			game->map.win_textures[1]))
		ft_error_handling(game, "Failed to load win texture 2");
	if (!load_textures3(game))
		return (0);
	return (1);
}

int	load_textures(t_game *game)
{
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
	if (!load_textures2(game))
		return (0);
	return (1);
}
