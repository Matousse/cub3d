/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 07:24:01 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/12 00:54:16 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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
	ft_printf("\n\n");
	ft_printf("    🌟 ⭐️ ✨ CONGRATULATIONS! ✨ ⭐️ 🌟\n");
	ft_printf("    ═══════════════════════════════\n");
	ft_printf("         You have completed\n");
	ft_printf("        the amazing maze!\n\n");
	ft_printf("    Thanks for playing this game!\n");
	ft_printf("    ═══════════════════════════════\n");
	ft_printf("\n\n");
}
