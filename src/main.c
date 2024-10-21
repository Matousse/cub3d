/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:31:40 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/21 23:36:36 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_bag *bag)
{
	if (keycode == 'W')
	{
		bag->camera.position.x += bag->camera.direction.x * MOVE_SPEED;
		bag->camera.position.y += bag->camera.direction.y * MOVE_SPEED;
	}
	if (keycode == 'S')
	{
		bag->camera.position.x += bag->camera.direction.x * MOVE_SPEED;
		bag->camera.position.y += bag->camera.direction.y * MOVE_SPEED;
	}
	if (keycode == 'A')
	{
		bag->camera.position.x += bag->camera.direction.x * MOVE_SPEED;
		bag->camera.position.y += bag->camera.direction.y * MOVE_SPEED;
	}
	if (keycode == 'D')
	{
		bag->camera.position.x += bag->camera.direction.x * MOVE_SPEED;
		bag->camera.position.y += bag->camera.direction.y * MOVE_SPEED;
	}
	return (0);
}

int	game_loop(t_bag *bag)
{
	cast_rays(bag);
	return (0);
}

int	main(void)
{
	t_bag	bag;
	int		i;

	init_game(&bag);
	mlx_hook(bag.win, 17, 0, close_window, &bag);
	mlx_hook(bag.win, 2, 1L << 0, key_press, &bag);
	mlx_loop_hook(bag.mlx, game_loop, &bag);
	mlx_loop(bag.mlx);
	i = 0;
	while (i < bag.map.height)
	{
		free(bag.map.map[i]);
		i++;
	}
	free(bag.map.map);
	return (0);
}
