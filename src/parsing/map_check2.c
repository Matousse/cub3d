/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:29:15 by dloisel           #+#    #+#             */
/*   Updated: 2024/12/12 08:19:02 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
			&& game->map.fullmap[i][j] != ' ' && game->map.fullmap[i][j] != 'N'
			&& game->map.fullmap[i][j] != 'W' && game->map.fullmap[i][j] != 'E'
			&&game->map.fullmap[i][j] != 'S')
				return ((void)ft_error_map("Invalid character within the map.", \
				game));
			j++;
		}
		i++;
	}
}

int	ft_find_player_pos(t_game *game)
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
