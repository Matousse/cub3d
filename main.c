/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:31:40 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/21 15:32:17 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MOVE_SPEED 0.05
#define ROTATE_SPEED 0.03

void	init_game(t_bag *bag)
{
	int	i;
	int	j;

	bag->map.width = 50;
	bag->map.height = 50;
	bag->map.map = malloc(sizeof(char *) * bag->map.height);
	i = 0;
	while (i < bag->map.height)
	{
		bag->map.map[i] = malloc(sizeof(char) * bag->map.width);
		j = 0;
		while (j < bag->map.width)
		{
			if (i == 0 || i == bag->map.height - 1 || j == 0
				|| j == bag->map.width - 1)
				bag->map.map[i][j] = '1';
			else
				{
					bag->map.map[i][j] = '0';
				}
				j++;
			}
			i++;
		}
		bag->camera.position.x = 10;
		bag->camera.position.y = 10;
		bag->camera.direction.x = 0;
		bag->camera.direction.y = 0;
		bag->camera.plane.x = 0;
		bag->camera.plane.y = 0.66;
		bag->camera.fov = 60 * M_PI / 180;
		bag->mlx = mlx_init();
		bag->win = mlx_new_window(bag->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
		bag->img = mlx_new_image(bag->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
		bag->addr = mlx_get_data_addr(bag->img, &bag->bits_per_pixel, &bag->line_length, &bag->endian);
	}

void	render_frame(t_bag *bag)
{
	int	x;

	(void)bag;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		x++;
	}
}

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
	render_frame(bag);
	mlx_put_image_to_window(bag->mlx, bag->win, bag->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_bag	bag;
	int		i;

	init_game(&bag);
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
