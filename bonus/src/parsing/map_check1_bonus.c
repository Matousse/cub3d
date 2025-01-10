/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check1_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:57:44 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/10 18:19:14 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	ft_wall_check3(t_game *game)
{
	int	i;
	int	j;

	i = 1;
	if (game->map.is_map_valid == 1)
		return ;
	while (game->map.fullmap[i + 1] != NULL)
	{
		j = 1;
		while (game->map.fullmap[i][j + 1] != '\0')
		{
			if (game->map.fullmap[i][j] == '0' \
			&& !ft_zero_map_check(game->map.fullmap, i, j))
				return ((void)ft_error_map("Missing wall within the map.", \
				game));
			j++;
		}
		i++;
	}
}

void	ft_wall_check2(t_game *game)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	if (game->map.is_map_valid == 1)
		return ;
	while (game->map.fullmap[i])
	{
		j = 0;
		len = ft_strlen(game->map.fullmap[i]);
		while (game->map.fullmap[i][j] == ' ')
			j++;
		if (game->map.fullmap[i][j] != '1' && game->map.fullmap[i][j] != ' ')
			return ((void)ft_error_map("Missing wall on the \
left side of the map.", game));
		if (game->map.fullmap[i][len - 1] != '1' \
		&& game->map.fullmap[i][len - 1] != ' ')
			return ((void)ft_error_map("Missing wall on the \
right side of the map.", game));
		i++;
	}
}

void	ft_wall_check1(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (game->map.is_map_valid == 1)
		return ;
	while (game->map.fullmap[0][i])
	{
		if (game->map.fullmap[0][i] != '1' && game->map.fullmap[0][i] != ' ')
			return ((void)ft_error_map("Missing wall in the \
first row of the map.", game));
		i++;
	}
	i = 0;
	while (game->map.fullmap[i])
		i++;
	i--;
	while (game->map.fullmap[i][j])
	{
		if (game->map.fullmap[i][j] != '1' && game->map.fullmap[i][j] != ' ')
			return ((void)ft_error_map("Missing wall in the last \
row of the map.", game));
		j++;
	}
}

void	ft_emptyline_check(t_game *game)
{
	int	i;
	int	j;
	int	is_empty;

	i = 0;
	while (game->map.fullmap[i])
	{
		j = 0;
		is_empty = 1;
		while (game->map.fullmap[i][j])
		{
			if (game->map.fullmap[i][j] != '\n' && \
			game->map.fullmap[i][j] != ' ')
			{
				is_empty = 0;
				break ;
			}
			j++;
		}
		if (is_empty)
			return ((void)ft_error_map("Empty line in the map.", game));
		i++;
	}
}

void	ft_map_check(t_game *game)
{
	if (game->map.is_map_valid == 1)
		return ;
	if (!game->map.fullmap)
		return ((void)ft_error_map("No map in the .cub file.", game));
	ft_invalid_char_check(game);
	if (game->map.is_map_valid == 1)
		return ;
	ft_emptyline_check(game);
	if (game->map.is_map_valid == 1)
		return ;
	ft_wall_check1(game);
	if (game->map.is_map_valid == 1)
		return ;
	ft_wall_check2(game);
	if (game->map.is_map_valid == 1)
		return ;
	ft_wall_check3(game);
	if (game->map.is_map_valid == 1)
		return ;
	ft_player_check(game, 0, 0);
}
