/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:12:16 by dloisel           #+#    #+#             */
/*   Updated: 2024/10/29 16:07:59 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_struct_map_init(t_bag *game)
{
	game->map.fullmap = NULL;
	game->map.is_map_valid = 0;
	game->map.all_info = 0;
}

void	ft_parsing(int argc, char **argv, t_bag *game)
{
	ft_struct_map_init(game);
	ft_arg_verif(argc, argv, game);
	ft_map_init(game, argv[1], 0);
	ft_map_check(game);
}
//Je check chaque ligne si le premier et dernier caractère est un 1
//Si je croise un espace je regarde si il est
//Je check chaque 0 si il est entouré de soit un 0 ou un 1
//Je check chaque espace si il est entouré de soit un 1 ou un autre espace
//Défauts du parsing :
//	- Si la première ou derniére ligne a des 0 qui dépassent alors la map est
//	  alors que la map est techniquement jouable.
