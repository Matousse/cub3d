/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:36:06 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/11 02:23:42 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

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
	array = NULL;
}

void	ft_error_map(char *msg, t_game *game)
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
	if (game->map.door_texture)
		free(game->map.door_texture);
	if (game->map.doors)
		free(game->map.doors);
	if (msg)
	{
		ft_printf(RED "%s\n", "Error");
		ft_printf("%s\n" RESET, msg);
	}
	exit(1);
}

void	ft_free_map(t_game *game)
{
	if (game->map.fullmap)
	{
		ft_free_array(game->map.fullmap);
		game->map.fullmap = NULL;
	}
	ft_free_textures(game);
	if (game->map.doors)
	{
		free(game->map.doors);
		game->map.doors = NULL;
	}
}

void	ft_free_map1(t_game *game)
{
	if (game->map.fullmap)
	{
		ft_free_array(game->map.fullmap);
		game->map.fullmap = NULL;
	}
	if (game->map.doors)
	{
		free(game->map.doors);
		game->map.doors = NULL;
	}
}

void	ft_free_textures(t_game *game)
{
	if (game->map.no_texture)
	{
		free(game->map.no_texture);
		game->map.no_texture = NULL;
	}
	if (game->map.so_texture)
	{
		free(game->map.so_texture);
		game->map.so_texture = NULL;
	}
	if (game->map.we_texture)
	{
		free(game->map.we_texture);
		game->map.we_texture = NULL;
	}
	ft_free_textures2(game);
	ft_free_win_textures(game);
}
