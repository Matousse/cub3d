/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:13:21 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/10 21:57:11 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	init_key_states(t_game *game)
{
	game->keys.w = 0;
	game->keys.s = 0;
	game->keys.a = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
}

void	handle_forward_back_move(t_game *game, double *move_x,
		double *move_y, double speed)
{
	if (game->keys.w)
	{
		*move_x += game->player.dir_x * speed;
		*move_y += game->player.dir_y * speed;
	}
	if (game->keys.s)
	{
		*move_x -= game->player.dir_x * speed;
		*move_y -= game->player.dir_y * speed;
	}
}

void	handle_lateral_move(t_game *game, double *move_x,
		double *move_y, double speed)
{
	if (game->keys.a)
	{
		*move_x -= game->player.dir_y * speed;
		*move_y += game->player.dir_x * speed;
	}
	if (game->keys.d)
	{
		*move_x += game->player.dir_y * speed;
		*move_y -= game->player.dir_x * speed;
	}
}

void	apply_movement(t_game *game, double move_x, double move_y)
{
	int	next_pos_x;
	int	next_pos_y;

	next_pos_x = (int)(game->player.pos_x + move_x);
	next_pos_y = (int)(game->player.pos_y + move_y);
	if (game->map.fullmap[next_pos_x][(int)game->player.pos_y]
		!= '1' && (game->map.fullmap[next_pos_x][(int)game->player.pos_y]
		!= 'D' || is_door_open(game, next_pos_x, (int)game->player.pos_y)))
		game->player.pos_x += move_x;
	if (game->map.fullmap[(int)game->player.pos_x][next_pos_y] != '1'
		&& (game->map.fullmap[(int)game->player.pos_x][next_pos_y] != 'D'
		|| is_door_open(game, (int)game->player.pos_x, next_pos_y)))
		game->player.pos_y += move_y;
}

void	update_movement(t_game *game)
{
	double	move_x;
	double	move_y;
	double	speed;

	move_x = 0;
	move_y = 0;
	speed = MOVE_SPEED;
	usleep(1000);
	if ((game->keys.w || game->keys.s) && (game->keys.a || game->keys.d))
		speed *= 0.707;
	handle_forward_back_move(game, &move_x, &move_y, speed);
	handle_lateral_move(game, &move_x, &move_y, speed);
	apply_movement(game, move_x, move_y);
	if (game->keys.left)
		handle_rotation_left(game);
	if (game->keys.right)
		handle_rotation_right(game);
}
