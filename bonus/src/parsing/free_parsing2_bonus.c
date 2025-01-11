/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:06:30 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/11 02:15:22 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	ft_free_textures2(t_game *game)
{
	if (game->map.ea_texture)
	{
		free(game->map.ea_texture);
		game->map.ea_texture = NULL;
	}
	if (game->map.door_texture)
	{
		free(game->map.door_texture);
		game->map.door_texture = NULL;
	}
	if (game->map.wallsmiley1_texture)
	{
		free(game->map.wallsmiley1_texture);
		game->map.wallsmiley1_texture = NULL;
	}
	if (game->map.wallsmiley2_texture)
	{
		free(game->map.wallsmiley2_texture);
		game->map.wallsmiley2_texture = NULL;
	}
}

void	ft_free_win_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		if (game->map.win_textures[i])
		{
			free(game->map.win_textures[i]);
			game->map.win_textures[i] = NULL;
		}
		i++;
	}
}
