/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:12:16 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/10 18:25:48 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	ft_struct_map_init(t_game *game)
{
	game->map.fullmap = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.is_map_valid = 0;
	game->map.all_info = 0;
	game->map.player_x = -1;
	game->map.player_y = -1;
	game->map.player_dir = '\0';
	game->map.floor_color = 0;
	game->map.ceiling_color = 0;
}

void	ft_get_width_height(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (game->map.is_map_valid == 1)
		return ;
	while (game->map.fullmap[i])
	{
		while (game->map.fullmap[i][j])
			j++;
		if (game->map.width < j)
			game->map.width = j;
		i++;
	}
	game->map.height = i;
}

void	ft_parsing(int argc, char **argv, t_game *game)
{
	ft_struct_map_init(game);
	ft_arg_verif(argc, argv, game);
	ft_map_init(game, argv[1], 0);
	ft_map_check(game);
	ft_get_width_height(game);
	if (game->map.is_map_valid == 1)
		ft_error_handling(game, NULL);
}
// Je check chaque ligne si le premier et dernier caractère est un 1
// Si je croise un espace je regarde si il est
// Je check chaque 0 si il est entouré de soit un 0 ou un 1
// Je check chaque espace si il est entouré de soit un 1 ou un autre espace
// Défauts du parsing :
//	- Si la première ou derniére ligne a des 0 qui dépassent alors la map est
//		alors que la map est techniquement jouable.
