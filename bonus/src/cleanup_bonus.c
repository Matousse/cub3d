/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 07:34:21 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/11 02:29:02 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	destroy_textures(t_game *game)
{
	int	i;

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
	i = 0;
	while (i < 9)
	{
		if (game->textures.win[i].img)
			mlx_destroy_image(game->mlx, game->textures.win[i].img);
		i++;
	}
}

void	cleanup_game(t_game *game)
{
	if (game)
	{
		ft_free_map(game);
		destroy_textures(game);
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		if (game->minimap)
		{
			if (game->minimap->img)
				mlx_destroy_image(game->mlx, game->minimap->img);
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
