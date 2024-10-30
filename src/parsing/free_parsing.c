/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:36:06 by dloisel           #+#    #+#             */
/*   Updated: 2024/10/29 22:00:49 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
	i++;
	}
	free(array);
}

void	ft_error_map(char *msg, t_bag *game)
{
	if (game->map.fullmap)
		ft_free_array(game->map.fullmap);
	ft_printf(RED "%s\n", "Error");
	ft_printf("%s\n" RESET, msg);
	game->map.is_map_valid = 1;
	game->map.fullmap = NULL;
}

void	ft_free_map(t_bag *game)
{
	if (game->map.fullmap)
		ft_free_array(game->map.fullmap);
	if (game->map.no_texture)
		free(game->map.no_texture);
	if (game->map.so_texture)
		free(game->map.so_texture);
	if (game->map.we_texture)
		free(game->map.we_texture);
	if (game->map.ea_texture)
		free(game->map.ea_texture);
}
