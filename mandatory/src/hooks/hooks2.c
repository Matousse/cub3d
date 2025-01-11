/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:00:55 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/11 01:11:59 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_window(game);
	else if (keycode == 119 || keycode == 115)
		handle_forward_backward(keycode, game);
	else if (keycode == 65361 || keycode == 65363)
		handle_rotation(keycode, game);
	else if (keycode == 100 || keycode == 97)
		handle_lateral(keycode, game);
	return (0);
}
