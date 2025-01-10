/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 07:34:21 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/10 15:32:22 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	destroy_textures(t_game *game)
{
	if (game->textures.north.img)
		mlx_destroy_image(game->mlx, game->textures.north.img);
	if (game->textures.south.img)
		mlx_destroy_image(game->mlx, game->textures.south.img);
	if (game->textures.east.img)
		mlx_destroy_image(game->mlx, game->textures.east.img);
	if (game->textures.west.img)
		mlx_destroy_image(game->mlx, game->textures.west.img);
	if (game->textures.door.img)
		mlx_destroy_image(game->mlx, game->textures.door.img);
	if (game->textures.wallsmiley1.img)
		mlx_destroy_image(game->mlx, game->textures.wallsmiley1.img);
	if (game->textures.wallsmiley2.img)
		mlx_destroy_image(game->mlx, game->textures.wallsmiley2.img);
}

void	cleanup_game(t_game *game)
{
	if (game)
	{
		destroy_textures(game);
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		if (game->minimap->img)
			mlx_destroy_image(game->mlx, game->minimap->img);
		if (game->minimap)
		{
			free(game->minimap);
			game->minimap = NULL;
		}
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
	}
}

int	close_window(t_game *game)
{
	ft_free_map(game);
	cleanup_game(game);
	exit(0);
	return (0);
}

int	ft_error_handling(t_game *game, char *message)
{
	if (!game->map.is_map_valid)
		ft_free_map(game);
	cleanup_game(game);
	if (message)
	{
		ft_printf(RED "%s\n", "Error");
		ft_printf("%s\n" RESET, message);
	}
	exit(1);
	return (1);
}
