/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:24:15 by dloisel           #+#    #+#             */
/*   Updated: 2024/10/29 22:01:00 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	ft_is_map_line(char *line)
{
	int	i;
	int	has_valid_char;

	i = 0;
	has_valid_char = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && \
		line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		if (line[i] != ' ')
			has_valid_char = 1;
		i++;
	}
	return (has_valid_char);
}

void	ft_copy_previous_map(char **new_map, char **old_map, int size)
{
	int	j;

	j = 0;
	while (old_map && old_map[j] && j < size)
	{
		new_map[j] = old_map[j];
		j++;
	}
}

int	ft_zero_map_check(char **map, int i, int j)
{
	if ((map[i - 1][j] != '1' && map[i - 1][j] != '0' && map[i - 1][j] != 'N' &&
		map[i - 1][j] != 'S' && map[i - 1][j] != 'W' && map[i - 1][j] != 'E') ||
		(map[i + 1][j] != '1' && map[i + 1][j] != '0' && map[i + 1][j] != 'N' &&
		map[i + 1][j] != 'S' && map[i + 1][j] != 'W' && map[i + 1][j] != 'E') ||
		(map[i][j - 1] != '1' && map[i][j - 1] != '0' && map[i][j - 1] != 'N' &&
		map[i][j - 1] != 'S' && map[i][j - 1] != 'W' && map[i][j - 1] != 'E') ||
		(map[i][j + 1] != '1' && map[i][j + 1] != '0' && map[i][j + 1] != 'N' &&
		map[i][j + 1] != 'S' && map[i][j + 1] != 'W' && map[i][j + 1] != 'E'))
		return (0);
	return (1);
}
