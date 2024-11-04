/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 03:23:43 by dmathis           #+#    #+#             */
/*   Updated: 2024/11/03 17:13:52 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#define MIN_WALL_DISTANCE 0.3

int	check_collision(t_bag *game, double new_x, double new_y)
{
    // Vérifier d'abord si on est dans un mur
    if (game->map.fullmap[(int)new_y][(int)new_x] == '1')
        return (1);

    // Vérifier la distance minimale au mur le plus proche
    double dist = get_distance_to_wall(game, new_x, new_y);
    return (dist < MIN_WALL_DISTANCE);
}

double	get_distance_to_wall(t_bag *game, double x, double y)
{
	int		map_x;
	int		map_y;
	double	dy;
	double	dist;

	map_x = (int)x;
	map_y = (int)y;
	double min_dist = 100000.0; // Une grande valeur initiale
	int i, j;
	// Vérifier tous les murs autour de la position
	for (i = map_y - 1; i <= map_y + 1; i++)
	{
		for (j = map_x - 1; j <= map_x + 1; j++)
		{
			if (i >= 0 && j >= 0 && i < game->map.height && j < game->map.width)
			{
				if (game->map.fullmap[i][j] == '1')
				{
					// Calculer la distance euclidienne au mur
					double dx = x - (j + 0.5); // +0.5 pour le centre du mur
					dy = y - (i + 0.5);
					dist = sqrt(dx * dx + dy * dy);
					if (dist < min_dist)
						min_dist = dist;
				}
			}
		}
	}
	return (min_dist);
}

void	ft_move_forward(t_bag *game)
{
	double	new_x;
	double	new_y;

	new_x = game->camera.position.x + game->camera.direction.x
		* game->camera.move_speed;
	new_y = game->camera.position.y + game->camera.direction.y
		* game->camera.move_speed;
	if (!check_collision(game, new_x, new_y))
	{
		game->camera.position.x = new_x;
		game->camera.position.y = new_y;
	}
}

void	ft_move_backward(t_bag *game)
{
	double	new_x;
	double	new_y;

	new_x = game->camera.position.x - game->camera.direction.x
		* game->camera.move_speed;
	new_y = game->camera.position.y - game->camera.direction.y
		* game->camera.move_speed;
	if (!check_collision(game, new_x, new_y))
	{
		game->camera.position.x = new_x;
		game->camera.position.y = new_y;
	}
}

void	ft_move_left(t_bag *game)
{
	double	perp_x;
	double	perp_y;
	double	new_x;
	double	new_y;

	perp_x = -game->camera.direction.y;
	perp_y = game->camera.direction.x;
	new_x = game->camera.position.x - perp_x * game->camera.move_speed;
	new_y = game->camera.position.y - perp_y * game->camera.move_speed;
	if (!check_collision(game, new_x, new_y))
	{
		game->camera.position.x = new_x;
		game->camera.position.y = new_y;
	}
}



void	ft_move_right(t_bag *game)
{
	double	perp_x;
	double	perp_y;
	double	new_x;
	double	new_y;

	perp_x = -game->camera.direction.y;
	perp_y = game->camera.direction.x;
	new_x = game->camera.position.x + perp_x * game->camera.move_speed;
	new_y = game->camera.position.y + perp_y * game->camera.move_speed;
	if (!check_collision(game, new_x, new_y))
	{
		game->camera.position.x = new_x;
		game->camera.position.y = new_y;
	}
}

void	ft_rotate_left(t_bag *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->camera.direction.x;
	game->camera.direction.x = game->camera.direction.x
		* cos(game->camera.rot_speed) - game->camera.direction.y
		* sin(game->camera.rot_speed);
	game->camera.direction.y = old_dir_x * sin(game->camera.rot_speed)
		+ game->camera.direction.y * cos(game->camera.rot_speed);
	old_plane_x = game->camera.plane.x;
	game->camera.plane.x = game->camera.plane.x * cos(game->camera.rot_speed)
		- game->camera.plane.y * sin(game->camera.rot_speed);
	game->camera.plane.y = old_plane_x * sin(game->camera.rot_speed)
		+ game->camera.plane.y * cos(game->camera.rot_speed);
}

void	ft_rotate_right(t_bag *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->camera.direction.x;
	game->camera.direction.x = game->camera.direction.x
		* cos(-game->camera.rot_speed) - game->camera.direction.y
		* sin(-game->camera.rot_speed);
	game->camera.direction.y = old_dir_x * sin(-game->camera.rot_speed)
		+ game->camera.direction.y * cos(-game->camera.rot_speed);
	old_plane_x = game->camera.plane.x;
	game->camera.plane.x = game->camera.plane.x * cos(-game->camera.rot_speed)
		- game->camera.plane.y * sin(-game->camera.rot_speed);
	game->camera.plane.y = old_plane_x * sin(-game->camera.rot_speed)
		+ game->camera.plane.y * cos(-game->camera.rot_speed);
}
