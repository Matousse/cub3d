/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:06:30 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/10 14:08:29 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
