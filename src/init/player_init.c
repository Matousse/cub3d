/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:34:20 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/30 03:50:02 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_init_player(t_bag *game)
{
	printf("Debug: ft_init_player start\n");

	// Vérifier si la map est valide
	if (!game->map.fullmap)
	{
		printf("Error: map is NULL\n");
		return (0);
	}

	printf("Debug: map dimensions - width: %d, height: %d\n", game->map.width,
		game->map.height);

	// Afficher le contenu de la map
	printf("Debug: Current map content:\n");
	int i = 0;
	while (i < game->map.height)
	{
		printf("%s\n", game->map.fullmap[i]);
		i++;
	}

	// Initialiser les positions à des valeurs invalides
	game->map.player_x = -1;
	game->map.player_y = -1;
	game->map.player_dir = '\0';

	printf("Debug: Finding player position...\n");
	if (!ft_find_player_pos(game))
	{
		printf("Error: Could not find player position in map\n");
		return (0);
	}

	printf("Debug: Player found at (%d, %d) facing %c\n", game->map.player_x,
		game->map.player_y, game->map.player_dir);

	printf("Debug: Initializing camera...\n");

	int ft_find_player_pos(t_bag * game)
	{
		int i;
		int j;

		i = 0;
		while (i < game->map.height)
		{
			j = 0;
			while (j < game->map.width)
			{
				if (ft_is_player(game->map.fullmap[i][j]))
				{
					game->map.player_x = j;
					game->map.player_y = i;
					game->map.player_dir = game->map.fullmap[i][j];
					return (1);
				}
				j++;
			}
			i++;
		}
		return (0);
	}

	int ft_is_player(char c)
	{
		return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
	}
