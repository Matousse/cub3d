/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:00:12 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/10 02:15:06 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// textures.c

#include "../../includes/cub3d.h"

int	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (0);
	texture->data = (int *)mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
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
	return (1);
}
