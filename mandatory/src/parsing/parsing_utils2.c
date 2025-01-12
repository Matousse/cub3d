/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:42:18 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/12 16:42:32 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	ft_is_valid_mapchar(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E' || c == 'D' || c == 'T' || c == 'X');
}

int	ft_zero_map_check2(char **map, int i, int j)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = map[i - 1][j];
	down = map[i + 1][j];
	left = map[i][j - 1];
	right = map[i][j + 1];
	return (ft_is_valid_mapchar(up)
		&& ft_is_valid_mapchar(down)
		&& ft_is_valid_mapchar(left)
		&& ft_is_valid_mapchar(right));
}
