/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:56:30 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/29 22:16:35 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_struct_init(t_bag *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->addr = NULL;
	game->bits_per_pixel = 0;
	game->line_length = 0;
	game->endian = 0;
	// Map initialization
	game->map.fullmap = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.no_texture = NULL;
	game->map.so_texture = NULL;
	game->map.we_texture = NULL;
	game->map.ea_texture = NULL;
	game->map.floor_color = 0;
	game->map.ceiling_color = 0;
	game->map.is_map_valid = 0;
	game->map.all_info = 0;
	game->map.player_x = -1;  // Ajout d'une valeur par défaut
	game->map.player_y = -1;  // Ajout d'une valeur par défaut
	game->map.player_dir = 0; // Ajout d'une valeur par défaut
	// Initialize textures
	game->no_texture.img = NULL;
	game->so_texture.img = NULL;
	game->we_texture.img = NULL;
	game->ea_texture.img = NULL;
	// Initialize camera
	game->camera.position.x = 0;
	game->camera.position.y = 0;
	game->camera.direction.x = 0;
	game->camera.direction.y = 0;
	game->camera.plane.x = 0;
	game->camera.plane.y = 0;
	game->camera.fov = 60 * M_PI / 180;
}

int	ft_init_mlx(t_bag *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!game->win)
		return (0);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img)
		return (0);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	if (!game->addr)
		return (0);
	return (1);
}
