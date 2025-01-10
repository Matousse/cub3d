/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:29:15 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/10 18:25:32 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

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
}
