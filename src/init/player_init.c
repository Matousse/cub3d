/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:34:20 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/30 14:28:59 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_init_player(t_bag *game)
{
	// Réinitialiser la caméra
	memset(&game->camera, 0, sizeof(t_camera));
	// Trouver la position du joueur
	if (!ft_find_player_pos(game))
		return ;
	// Initialiser la caméra
	game->camera.position.x = game->map.player_x + 0.5;
	game->camera.position.y = game->map.player_y + 0.5;
	game->camera.move_speed = 0.05;
	game->camera.rot_speed = 0.03;
	// Initialiser la direction et le plan basé sur l'orientation initiale
	if (game->map.player_dir == 'N')
	{
		game->camera.direction.x = 0;
		game->camera.direction.y = -1;
		game->camera.plane.x = 0.66;
		game->camera.plane.y = 0;
	}
	else if (game->map.player_dir == 'S')
	{
		game->camera.direction.x = 0;
		game->camera.direction.y = 1;
		game->camera.plane.x = -0.66;
		game->camera.plane.y = 0;
	}
	else if (game->map.player_dir == 'E')
	{
		game->camera.direction.x = 1;
		game->camera.direction.y = 0;
		game->camera.plane.x = 0;
		game->camera.plane.y = 0.66;
	}
	else if (game->map.player_dir == 'W')
	{
		game->camera.direction.x = -1;
		game->camera.direction.y = 0;
		game->camera.plane.x = 0;
		game->camera.plane.y = -0.66;
	}
	printf("Camera initialized:\n");
	printf("Position: (%f, %f)\n", game->camera.position.x,
		game->camera.position.y);
	printf("Direction: (%f, %f)\n", game->camera.direction.x,
		game->camera.direction.y);
	printf("Plane: (%f, %f)\n", game->camera.plane.x, game->camera.plane.y);
}

int	ft_find_player_pos(t_bag *game)
{
	int	i;
	int	j;

	printf("Finding player in map of size %dx%d\n", game->map.width,
		game->map.height);
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			printf("%c", game->map.fullmap[i][j]); // Print the map
			if (game->map.fullmap[i][j] == 'N' || game->map.fullmap[i][j] == 'S'
				|| game->map.fullmap[i][j] == 'E'
				|| game->map.fullmap[i][j] == 'W')
			{
				game->map.player_x = j;
				game->map.player_y = i;
				game->map.player_dir = game->map.fullmap[i][j];
				printf("\nFound player at (%d,%d) facing %c\n", j, i,
					game->map.fullmap[i][j]);
				return (1);
			}
			j++;
		}
		printf("\n");
		i++;
	}
	return (0);
}

int	ft_is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
