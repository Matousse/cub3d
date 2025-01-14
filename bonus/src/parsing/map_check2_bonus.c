/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:29:15 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/11 02:18:10 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	ft_player_check(t_game *game, int i, int j)
{
	int	player_count;

	player_count = 0;
	if (game->map.is_map_valid == 1)
		return ;
	while (game->map.fullmap[i])
	{
		j = 0;
		while (game->map.fullmap[i][j])
		{
			if (game->map.fullmap[i][j] == 'N' || \
			game->map.fullmap[i][j] == 'S' || game->map.fullmap[i][j] == 'E' \
			|| game->map.fullmap[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count == 0)
		return ((void)ft_error_map("No player is present within the map.", \
		game));
	else if (player_count > 1)
		return ((void)ft_error_map("Two or more players are present \
within the map, only one player is allowed to be on the map.", game));
}

void	ft_invalid_char_check(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.fullmap[i])
	{
		j = 0;
		while (game->map.fullmap[i][j])
		{
			if (game->map.fullmap[i][j] != '1' && game->map.fullmap[i][j] != '0'
				&& game->map.fullmap[i][j] != ' '
					&& game->map.fullmap[i][j] != 'N'
				&& game->map.fullmap[i][j] != 'W'
					&& game->map.fullmap[i][j] != 'E'
				&& game->map.fullmap[i][j] != 'S'
					&& game->map.fullmap[i][j] != 'D'
				&& game->map.fullmap[i][j] != 'T'
					&& game->map.fullmap[i][j] != 'X')
			{
				ft_error_map("Invalid character within the map.", game);
			}
			j++;
		}
		i++;
	}
}

int	ft_needs_wall_check(char c)
{
	return (c == '0' || c == 'T' || c == 'X'
		|| c == 'N' || c == 'W' || c == 'E' || c == 'S');
}
