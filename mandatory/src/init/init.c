/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:20:50 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/11 02:07:47 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	init_player_direction(t_game *game, char direction)
{
	if (direction == 'N')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
	else if (direction == 'S')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = -0.66;
	}
	init_player_direction2(game, direction);
}

void	init_player_direction2(t_game *game, char direction)
{
	if (direction == 'E')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
	else if (direction == 'W')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
	}
}

void	find_player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.fullmap[i])
	{
		j = 0;
		while (game->map.fullmap[i][j])
		{
			if (game->map.fullmap[i][j] == 'N'
				|| game->map.fullmap[i][j] == 'S' ||
				game->map.fullmap[i][j] == 'E'
					|| game->map.fullmap[i][j] == 'W')
			{
				game->player.pos_x = i + 0.5;
				game->player.pos_y = j + 0.5;
				init_player_direction(game, game->map.fullmap[i][j]);
				game->map.fullmap[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

int	init_mlx_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "Cub3D");
	if (!game->win)
		return (0);
	return (1);
}

int	init_mlx_image(t_game *game)
{
	int	bpp;
	int	size_line;
	int	endian;

	bpp = 32;
	size_line = WINDOW_WIDTH * 4;
	endian = 0;
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
		return (0);
	game->addr = mlx_get_data_addr(game->img, &bpp, &size_line, &endian);
	if (!game->addr)
		return (0);
	game->bits_per_pixel = bpp;
	game->line_length = size_line;
	game->endian = endian;
	return (1);
}
