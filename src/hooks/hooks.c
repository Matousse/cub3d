/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 03:20:35 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/30 03:20:44 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_setup_hooks(t_bag *game)
{
	mlx_hook(game->win, 17, 0, ft_close_window, game);
	mlx_hook(game->win, 2, 1L << 0, ft_key_press, game);
	mlx_loop_hook(game->mlx, ft_game_loop, game);
}

int	ft_close_window(t_bag *game)
{
	ft_cleanup(game);
	exit(0);
	return (0);
}

int	ft_key_press(int keycode, t_bag *game)
{
	if (keycode == KEY_ESC)
		ft_close_window(game);
	if (keycode == KEY_W)
		ft_move_forward(game);
	if (keycode == KEY_S)
		ft_move_backward(game);
	if (keycode == KEY_A)
		ft_move_left(game);
	if (keycode == KEY_D)
		ft_move_right(game);
	if (keycode == KEY_LEFT)
		ft_rotate_left(game);
	if (keycode == KEY_RIGHT)
		ft_rotate_right(game);
	return (0);
}
