/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:17:57 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/11 02:34:17 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

int	key_release(int keycode, t_game *game)
{
	if (keycode == 119)
		game->keys.w = 0;
	else if (keycode == 115)
		game->keys.s = 0;
	else if (keycode == 97)
		game->keys.a = 0;
	else if (keycode == 100)
		game->keys.d = 0;
	else if (keycode == 65361)
		game->keys.left = 0;
	else if (keycode == 65363)
		game->keys.right = 0;
	return (0);
}

void	toggle_victory(t_game *game)
{
	int		player_map_x;
	int		player_map_y;
	int		x;
	int		y;

	player_map_x = (int)game->player.pos_x;
	player_map_y = (int)game->player.pos_y;
	x = player_map_x - 1;
	while (x <= player_map_x + 1)
	{
		y = player_map_y - 1;
		while (y <= player_map_y + 1)
		{
			if (x >= 0 && y >= 0 && game->map.fullmap[x]
				&& game->map.fullmap[x][y] == 'X')
			{
				display_victory_screen();
				close_window(game);
			}
			y++;
		}
		x++;
	}
}
