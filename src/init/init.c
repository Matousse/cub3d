/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 06:33:50 by dloisel           #+#    #+#             */
/*   Updated: 2024/12/12 09:01:38 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Initialisation */
void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
								  &game->line_length, &game->endian);
	/* Chargement des textures */
	if (!load_textures(game))
	{
		ft_error_handling(game, "One of the textures couldn't be loaded.");
		/*Ici free les textures qui ont réussi à charger sinon leak si ce n'est pas la première texture qui échoue*/
		exit(1);
	}
	// /* Initialisation de la carte */
	game->map_width = 8;
	game->map_height = 8;
	game->map = malloc(sizeof(int *) * game->map_height);
	for (int i = 0; i < game->map_height; i++)
	{
		game->map[i] = malloc(sizeof(int) * game->map_width);
		/* Ici mettre une protection du malloc et une fonction pour free le tableau sinon leak potentiel*/
		for (int j = 0; j < game->map_width; j++)
			game->map[i][j] = default_map[i][j];
	}
	/* Initialisation du joueur */
	game->player.pos_x =(double)game->map.player_x;
	game->player.pos_y = (double)game->map.player_y;
	game->player.dir_x = 1.0; //À changer en fonction de la direction trouvée en pendant le parsing
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
}
