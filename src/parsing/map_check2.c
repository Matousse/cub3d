/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:29:15 by dloisel           #+#    #+#             */
/*   Updated: 2024/11/08 21:31:23 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void ft_player_check(t_map *map, int i, int j)
{
    int player_count;

    player_count = 0;
    printf("Checking for player starting at i=%d, j=%d\n", i, j);  // Debug
    if (game->map->is_map_valid == 1)
        return;
    while (game->map->fullmap[i])
    {
        j = 0;
        while (game->map->fullmap[i][j])
        {
            printf("Checking position [%d][%d]: '%c'\n", i, j, game->map->fullmap[i][j]);  // Debug
            if (game->map->fullmap[i][j] == 'N' || 
                game->map->fullmap[i][j] == 'S' || 
                game->map->fullmap[i][j] == 'E' || 
                game->map->fullmap[i][j] == 'W')
            {
                printf("Found player: pos=%d,%d dir=%c\n", j, i, game->map->fullmap[i][j]);  // Debug
                game->map->player_x = j;
                game->map->player_y = i;
                game->map->player_dir = game->map->fullmap[i][j];
                player_count++;
            }
            j++;
        }
        i++;
    }
    printf("Player count: %d\n", player_count);  // Debug
    printf("Final player state: x=%d, y=%d, dir=%c\n", 
           game->map->player_x, game->map->player_y, game->map->player_dir);  // Debug
}

void	ft_invalid_char_check(t_bag *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map->fullmap[i])
	{
		j = 0;
		while (game->map->fullmap[i][j])
		{
			if (game->map->fullmap[i][j] != '1' && game->map->fullmap[i][j] != '0'
			&& game->map->fullmap[i][j] != ' ' && game->map->fullmap[i][j] != 'N'
			&& game->map->fullmap[i][j] != 'W' && game->map->fullmap[i][j] != 'E'
			&&game->map->fullmap[i][j] != 'S')
				return ((void)ft_error_map("Invalid character within the map.", \
				game));
			j++;
		}
		i++;
	}
}
