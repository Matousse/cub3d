/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:00:12 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/11 03:34:57 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// textures.c

#include "../../../includes/cub3d_bonus.h"

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
	if (game->map.win_textures[2] && !load_texture(game, &game->textures.win[2],
			game->map.win_textures[2]))
		ft_error_handling(game, "Failed to load win texture 3");
	if (game->map.win_textures[3] && !load_texture(game, &game->textures.win[3],
			game->map.win_textures[3]))
		ft_error_handling(game, "Failed to load win texture 4");
	if (game->map.win_textures[4] && !load_texture(game, &game->textures.win[4],
			game->map.win_textures[4]))
		ft_error_handling(game, "Failed to load win texture 5");
	if (!load_textures3(game))
		return (0);
	load_textures4(game);
	return (1);
}

int	load_textures4(t_game *game)
{
	if (game->map.win_textures[5] && !load_texture(game, &game->textures.win[5],
			game->map.win_textures[5]))
		ft_error_handling(game, "Failed to load win texture 6");
	if (game->map.win_textures[6] && !load_texture(game, &game->textures.win[6],
			game->map.win_textures[6]))
		ft_error_handling(game, "Failed to load win texture 7");
	if (game->map.win_textures[7] && !load_texture(game, &game->textures.win[7],
			game->map.win_textures[7]))
		ft_error_handling(game, "Failed to load win texture 8");
	if (game->map.win_textures[8] && !load_texture(game, &game->textures.win[8],
			game->map.win_textures[8]))
		ft_error_handling(game, "Failed to load win texture 9");
	return (0);
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
