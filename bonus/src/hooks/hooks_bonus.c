/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:48:27 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/12 01:20:08 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	handle_forward_backward(int keycode, t_game *game)
{
	double	margin;

	margin = 0.1;
	if (keycode == 119)
	{
		if (game->map.fullmap[(int)(game->player.pos_x + game->player.dir_x
				* (MOVE_SPEED + margin))][(int)game->player.pos_y] != '1')
			game->player.pos_x += game->player.dir_x * MOVE_SPEED;
		if (game->map.fullmap[(int)game->player.pos_x]
			[(int)(game->player.pos_y
				+ game->player.dir_y * (MOVE_SPEED + margin))] != '1')
			game->player.pos_y += game->player.dir_y * MOVE_SPEED;
	}
	else if (keycode == 115)
	{
		if (game->map.fullmap[(int)(game->player.pos_x - game->player.dir_x
				* (MOVE_SPEED + margin))][(int)game->player.pos_y] != '1')
			game->player.pos_x -= game->player.dir_x * MOVE_SPEED;
		if (game->map.fullmap[(int)game->player.pos_x]
			[(int)(game->player.pos_y - game->player.dir_y
				* (MOVE_SPEED + margin))] != '1')
			game->player.pos_y -= game->player.dir_y * MOVE_SPEED;
	}
}

void	handle_rotation_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-ROTATION_SPEED)
		- game->player.dir_y * sin(-ROTATION_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROTATION_SPEED)
		+ game->player.dir_y * cos(-ROTATION_SPEED);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x
		* cos(-ROTATION_SPEED) - game->player.plane_y * sin(-ROTATION_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROTATION_SPEED)
		+ game->player.plane_y * cos(-ROTATION_SPEED);
}

void	handle_rotation_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x
		* cos(ROTATION_SPEED) - game->player.dir_y * sin(ROTATION_SPEED);
	game->player.dir_y = old_dir_x * sin(ROTATION_SPEED) + game->player.dir_y
		* cos(ROTATION_SPEED);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x
		* cos(ROTATION_SPEED) - game->player.plane_y * sin(ROTATION_SPEED);
	game->player.plane_y = old_plane_x
		* sin(ROTATION_SPEED) + game->player.plane_y * cos(ROTATION_SPEED);
}

void	handle_rotation(int keycode, t_game *game)
{
	if (keycode == 65363)
		handle_rotation_right(game);
	else if (keycode == 65361)
		handle_rotation_left(game);
}

void	handle_lateral(int keycode, t_game *game)
{
	double	margin;

	margin = 0.1;
	if (keycode == 97)
	{
		if (game->map.fullmap[(int)(game->player.pos_x)]
			[(int)(game->player.pos_y + game->player.dir_x
							* (MOVE_SPEED + margin))] != '1')
			game->player.pos_y += game->player.dir_x * MOVE_SPEED;
		if (game->map.fullmap[(int)(game->player.pos_x - game->player.dir_y
				* (MOVE_SPEED + margin))][(int)game->player.pos_y] != '1')
			game->player.pos_x -= game->player.dir_y * MOVE_SPEED;
	}
	else if (keycode == 100)
	{
		if (game->map.fullmap[(int)(game->player.pos_x)]
			[(int)(game->player.pos_y - game->player.dir_x
							* (MOVE_SPEED + margin))] != '1')
			game->player.pos_y -= game->player.dir_x * MOVE_SPEED;
		if (game->map.fullmap[(int)(game->player.pos_x + game->player.dir_y
				* (MOVE_SPEED + margin))][(int)game->player.pos_y] != '1')
			game->player.pos_x += game->player.dir_y * MOVE_SPEED;
	}
}
