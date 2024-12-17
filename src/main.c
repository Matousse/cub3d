/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 07:24:01 by dloisel           #+#    #+#             */
/*   Updated: 2024/12/14 01:01:32 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Point d'entrée */
int main(int argc, char **argv)
{
	t_game game;

	// Initialiser la structure à zéro
	ft_memset(&game, 0, sizeof(t_game));

	ft_parsing(argc, argv, &game);
	// Initialiser le jeu
	init_game(&game);

	if (!game.mlx || !game.win || !game.img || !game.addr)
	{
		cleanup_game(&game);
		return (1);
	}

	// Configurer les hooks
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	mlx_loop_hook(game.mlx, render, &game);

	// Démarrer la boucle principale
	mlx_loop(game.mlx);

	return (0);
}

// void debug_print_map(t_game *game)
// {
//     printf("Current map state:\n");
//     for (int i = 0; i < game->map_height; i++)
//     {
//         for (int j = 0; j < game->map_width; j++)
//         {
//             printf("%c ", game->map[i][j]);
//         }
//         printf("\n");
//     }
//     printf("Player position: x=%f, y=%f\n", game->player.pos_x, game->player.pos_y);
//     printf("Player direction: dx=%f, dy=%f\n", game->player.dir_x, game->player.dir_y);
// }
