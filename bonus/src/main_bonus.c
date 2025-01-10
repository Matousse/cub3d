/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 07:24:01 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/11 00:45:41 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/* Point d'entrée */
int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	ft_parsing(argc, argv, &game);
	init_game(&game);
	if (!game.mlx || !game.win || !game.img || !game.addr)
	{
		cleanup_game(&game);
		return (1);
	}
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 6, 1L << 6, handle_mouse, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	return (0);
}
void	display_victory_screen(void)
{
	printf("\n\n");
	printf("    🌟 ⭐️ ✨ CONGRATULATIONS! ✨ ⭐️ 🌟\n");
	printf("    ═══════════════════════════════\n");
	printf("         You have completed\n");
	printf("        the amazing maze!\n\n");
	printf("    Thanks for playing this game!\n");
	printf("    ═══════════════════════════════\n");
	printf("\n\n");
}
