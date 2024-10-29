/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:45:12 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/29 16:39:31 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_texture_file(char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

t_texture	ft_load_texture(t_bag *game, char *path)
{
	t_texture	tex;

	// Initialiser la texture à 0
	ft_memset(&tex, 0, sizeof(t_texture));
	// Vérifier le chemin
	if (!path)
	{
		ft_error_map("Texture path is NULL", game);
		return (tex);
	}
	// Vérifier l'existence du fichier
	if (!check_texture_file(path))
	{
		ft_error_map("Texture file not found", game);
		return (tex);
	}
	// Charger l'image
	tex.img = mlx_xpm_file_to_image(game->mlx, path, &tex.width, &tex.height);
	if (!tex.img)
	{
		ft_error_map("Failed to load texture image", game);
		return (tex);
	}
	// Obtenir l'adresse des données
	tex.addr = mlx_get_data_addr(tex.img, &tex.bits_per_pixel, &tex.line_length,
			&tex.endian);
	if (!tex.addr)
	{
		mlx_destroy_image(game->mlx, tex.img);
		tex.img = NULL;
		ft_error_map("Failed to get texture data", game);
		return (tex);
	}
	return (tex);
}

int	ft_load_all_textures(t_bag *game)
{
	if (!check_texture_file(game->map.no_texture)
		|| !check_texture_file(game->map.so_texture)
		|| !check_texture_file(game->map.we_texture)
		|| !check_texture_file(game->map.ea_texture))
	{
		ft_error_map("One or more texture files are missing", game);
		return (0);
	}
	game->no_texture = ft_load_texture(game, game->map.no_texture);
	if (!game->no_texture.img)
		return (0);
	game->so_texture = ft_load_texture(game, game->map.so_texture);
	if (!game->so_texture.img)
	{
		mlx_destroy_image(game->mlx, game->no_texture.img);
		return (0);
	}
	return (1);
}
