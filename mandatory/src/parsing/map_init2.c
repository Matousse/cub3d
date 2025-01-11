/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 00:06:37 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/11 15:33:35 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	ft_allocate_new_line(t_game *game, size_t len, int i)
{
	game->map.fullmap[i] = malloc(sizeof(char) * (len + 1));
	if (!game->map.fullmap[i])
	{
		free(game->map.fullmap);
		ft_error_map("Allocation error.", game);
	}
}

size_t	ft_get_line_length(char *buff)
{
	size_t	len;

	len = 0;
	while (buff[len] && buff[len] != '\n')
		len++;
	return (len);
}

void	ft_copy_line(t_game *game, char *buff, size_t len, int i)
{
	int	j;

	j = -1;
	while (++j < (int)len)
		game->map.fullmap[i][j] = buff[j];
	game->map.fullmap[i][j] = '\0';
	game->map.fullmap[i + 1] = NULL;
}

void	ft_extract_info2(t_game *game, char *buff)
{
	if (!ft_strncmp(buff, "EA ", 3))
	{
		game->map.all_info++;
		if (!game->map.ea_texture)
			game->map.ea_texture = ft_extract_line_info(buff, game);
	}
	else if (!ft_strncmp(buff, "F ", 2))
	{
		game->map.all_info++;
		if (!game->map.floor_color)
			game->map.floor_color = ft_extract_color(buff, game);
	}
	else if (!ft_strncmp(buff, "C ", 2))
	{
		game->map.all_info++;
		if (!game->map.ceiling_color)
			game->map.ceiling_color = ft_extract_color(buff, game);
	}
}
