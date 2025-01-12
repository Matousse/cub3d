/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 07:24:01 by dloisel           #+#    #+#             */
/*   Updated: 2025/01/12 01:21:54 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	display_victory_screen(void)
{
	printf("\n\n");
	printf(GREEN"    🌟 ⭐️ ✨ CONGRATULATIONS! ✨ ⭐️ 🌟\n");
	printf("     ═══════════════════════════════\n");
	printf("           You have completed\n");
	printf("       	   the amazing maze!\n\n");
	printf("      Thanks for playing this game!\n");
	printf("     ═══════════════════════════════\n"RESET);
	printf("\n\n");
}

void	display_control(void)
{
	ft_printf("\n");
	ft_printf(YELLOW"Welcome to cub3d by double D\n"RESET);
	ft_printf("\n");
	ft_printf(BLUE"Here are the controls: \n");
	ft_printf(" - < WASD > --> To move the character.\n");
	ft_printf(" - < E > --> Open doors and interact with the WIN tile.\n");
	ft_printf(" - Left/Right arrows --> Allows you to move the camera.\n");
	ft_printf(" - The mouse allows you to control the camera,\n"RESET);
	ft_printf("\n");
	ft_printf(YELLOW"The goal of the game is to find the WINDOWS logo.\n");
	ft_printf("Good luck!!!\n"RESET);
}

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
	display_control();
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 6, 1L << 6, handle_mouse, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	return (0);
}
