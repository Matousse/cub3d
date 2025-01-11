/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init3_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 01:00:29 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/11 01:29:59 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	ft_extract_info4(t_game *game, char *buff)
{
	int	i;

	if (!ft_strncmp(buff, "WIN", 3) && buff[3] >= '1' && buff[3] <= '9')
	{
		game->map.all_info++;
		i = buff[3] - '1';
		if (!game->map.win_textures[i])
			game->map.win_textures[i] = ft_extract_line_info(buff + 4, game);
	}
}
