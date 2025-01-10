/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:00:55 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/10 14:36:48 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	toggle_door(t_game *game)
{
	int		player_map_x;
	int		player_map_y;
	double	check_distance;
	int		i;

	player_map_x = (int)game->player.pos_x;
	player_map_y = (int)game->player.pos_y;
	i = 0;
	while (i < game->map.nb_doors)
	{
		check_distance = sqrt(pow(game->player.pos_x - game->map.doors[i].x, 2)
				+ pow(game->player.pos_y - game->map.doors[i].y, 2));
		if (check_distance < 2.0)
		{
			if (game->map.doors[i].state == 1)
				game->map.doors[i].state = 0;
			else
				game->map.doors[i].state = 1;
			return ;
		}
		i++;
	}
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_window(game);
	else if (keycode == 119 || keycode == 115)
		handle_forward_backward(keycode, game);
	else if (keycode == 65363 || keycode == 65361)
		handle_rotation(keycode, game);
	else if (keycode == 100 || keycode == 97)
		handle_lateral(keycode, game);
	else if (keycode == 101)
		toggle_door(game);
	return (0);
}

int	handle_mouse(int x, int y, t_game *game)
{
	double	rotation_speed;
	int		delta_x;
	double	old_dir_x;
	double	old_plane_x;

	rotation_speed = 0.001;
	delta_x = x - (WINDOW_WIDTH / 2);
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(-rotation_speed * delta_x)
		- game->player.dir_y * sin(-rotation_speed * delta_x);
	game->player.dir_y = old_dir_x * sin(-rotation_speed * delta_x)
		+ game->player.dir_y * cos(-rotation_speed * delta_x);
	game->player.plane_x = game->player.plane_x * cos(-rotation_speed * delta_x)
		- game->player.plane_y * sin(-rotation_speed * delta_x);
	game->player.plane_y = old_plane_x * sin(-rotation_speed * delta_x)
		+ game->player.plane_y * cos(-rotation_speed * delta_x);
	return (0);
}