/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:24:15 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/12 16:41:49 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

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
	int	curr_len;
	int	prev_len;
	int	next_len;

	if (!map || !map[i] || i <= 0 || !map[i - 1] || !map[i + 1])
		return (0);
	curr_len = ft_strlen(map[i]);
	prev_len = ft_strlen(map[i - 1]);
	next_len = ft_strlen(map[i + 1]);
	if (j <= 0 || j >= curr_len - 1 || j >= prev_len
		|| j >= next_len)
		return (0);
	return (ft_zero_map_check2(map, i, j));
}

int	ft_needs_wall_check(char c)
{
	return (c == '0' || c == 'N' || c == 'W'
		|| c == 'E' || c == 'S');
}
