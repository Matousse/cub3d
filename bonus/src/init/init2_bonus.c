/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:29:15 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/10 18:17:14 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	init_game(t_game *game)
{
	if (!init_mlx_window(game))
		ft_error_handling(game, "MLX initialization failed");
	if (!init_mlx_image(game))
	{
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		mlx_destroy_window(game->mlx, game->win);
		ft_error_handling(game, "Image initialization failed");
	}
	if (!load_textures(game))
		ft_error_handling(game, "Loading textures failed");
	find_player_position(game);
	init_minimap(game);
	init_doors(game);
	game->animation.frame_count = 0;
	game->animation.current_frame = 0;
	game->animation.last_update = 0;
}

int	count_doors(t_game *game)
{
	int	i;
	int	j;
	int	door_count;

	door_count = 0;
	i = 0;
	while (game->map.fullmap[i])
	{
		j = 0;
		while (game->map.fullmap[i][j])
		{
			if (game->map.fullmap[i][j] == 'D')
				door_count++;
			j++;
		}
		i++;
	}
	return (door_count);
}

void	init_doors2(t_game *game)
{
	int	i;
	int	j;
	int	door_count;

	door_count = 0;
	i = 0;
	while (game->map.fullmap[i])
	{
		j = 0;
		while (game->map.fullmap[i][j])
		{
			if (game->map.fullmap[i][j] == 'D')
			{
				game->map.doors[door_count].x = i;
				game->map.doors[door_count].y = j;
				game->map.doors[door_count].state = DOOR_CLOSED;
				door_count++;
			}
			j++;
		}
		i++;
	}
}

void	init_doors(t_game *game)
{
	int	door_count;

	door_count = count_doors(game);
	game->map.doors = malloc(sizeof(t_door) * door_count);
	if (!game->map.doors)
		ft_error_map("Door allocation failed.", game);
	game->map.nb_doors = door_count;
	init_doors2(game);
}
