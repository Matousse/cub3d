/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 03:23:43 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/30 03:47:31 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_move_forward(t_bag *game)
{
	if (game->map.fullmap[(int)game->camera.position.y][(int)(game->camera.position.x
			+ game->camera.direction.x * game->camera.move_speed)] != '1')
		game->camera.position.x += game->camera.direction.x
			* game->camera.move_speed;
	if (game->map.fullmap[(int)(game->camera.position.y
			+ game->camera.direction.y
			* game->camera.move_speed)][(int)game->camera.position.x] != '1')
		game->camera.position.y += game->camera.direction.y
			* game->camera.move_speed;
}

void	ft_move_backward(t_bag *game)
{
	if (game->map.fullmap[(int)game->camera.position.y][(int)(game->camera.position.x
			- game->camera.direction.x * game->camera.move_speed)] != '1')
		game->camera.position.x -= game->camera.direction.x
			* game->camera.move_speed;
	if (game->map.fullmap[(int)(game->camera.position.y
			- game->camera.direction.y
			* game->camera.move_speed)][(int)game->camera.position.x] != '1')
		game->camera.position.y -= game->camera.direction.y
			* game->camera.move_speed;
}

void	ft_move_left(t_bag *game)
{
	double	perp_x;
	double	perp_y;

	perp_x = -game->camera.direction.y;
	perp_y = game->camera.direction.x;
	if (game->map.fullmap[(int)game->camera.position.y][(int)(game->camera.position.x
			- perp_x * game->camera.move_speed)] != '1')
		game->camera.position.x -= perp_x * game->camera.move_speed;
	if (game->map.fullmap[(int)(game->camera.position.y - perp_y
			* game->camera.move_speed)][(int)game->camera.position.x] != '1')
		game->camera.position.y -= perp_y * game->camera.move_speed;
}

void	ft_move_right(t_bag *game)
{
	double	perp_x;
	double	perp_y;

	perp_x = -game->camera.direction.y;
	perp_y = game->camera.direction.x;
	if (game->map.fullmap[(int)game->camera.position.y][(int)(game->camera.position.x
			+ perp_x * game->camera.move_speed)] != '1')
		game->camera.position.x += perp_x * game->camera.move_speed;
	if (game->map.fullmap[(int)(game->camera.position.y + perp_y
			* game->camera.move_speed)][(int)game->camera.position.x] != '1')
		game->camera.position.y += perp_y * game->camera.move_speed;
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
