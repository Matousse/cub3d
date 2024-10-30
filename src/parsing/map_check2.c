/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:29:15 by dloisel           #+#    #+#             */
/*   Updated: 2024/10/29 22:00:55 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_player_check(t_bag *game, int i, int j)
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
