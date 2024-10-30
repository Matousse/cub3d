/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:34:20 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/29 22:14:50 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_find_player_pos(t_bag *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.fullmap[i][j] == 'N' || game->map.fullmap[i][j] == 'S'
				|| game->map.fullmap[i][j] == 'E'
				|| game->map.fullmap[i][j] == 'W')
			{
				game->map.player_x = j;
				game->map.player_y = i;
				game->map.player_dir = game->map.fullmap[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
}

void	ft_init_player_dir(t_bag *game)
{
	// Set initial position (center of the tile)
	game->camera.position.x = game->map.player_x + 0.5;
	game->camera.position.y = game->map.player_y + 0.5;
	// Set direction and camera plane based on initial direction
	if (game->map.player_dir == 'N')
	{
		game->camera.direction = (t_vector){0, -1};
		game->camera.plane = (t_vector){0.66, 0};
	}
	else if (game->map.player_dir == 'S')
	{
		game->camera.direction = (t_vector){0, 1};
		game->camera.plane = (t_vector){-0.66, 0};
	}
	else if (game->map.player_dir == 'E')
	{
		game->camera.direction = (t_vector){1, 0};
		game->camera.plane = (t_vector){0, 0.66};
	}
	else if (game->map.player_dir == 'W')
	{
		game->camera.direction = (t_vector){-1, 0};
		game->camera.plane = (t_vector){0, -0.66};
	}
}

void	ft_init_player(t_bag *game)
{
	ft_find_player_pos(game);
	if (game->map.player_x < 0 || game->map.player_y < 0
		|| !game->map.player_dir)
	{
		ft_error_map("Invalid player position or direction", game);
		return ;
	}
	ft_init_player_dir(game);
	game->camera.fov = 60 * M_PI / 180;
}
