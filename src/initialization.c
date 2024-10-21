/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:56:30 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/21 23:47:30 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init2(t_bag *bag)
{
	bag->camera.position.x = 10;
	bag->camera.position.y = 10;
	bag->camera.direction.x = 0;
	bag->camera.direction.y = 1;
	bag->camera.plane.x = 0;
	bag->camera.plane.y = 1;
	bag->camera.fov = 60 * 3.14159265358979323846 / 180;
	bag->mlx = mlx_init();
	bag->win = mlx_new_window(bag->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	bag->img = mlx_new_image(bag->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	bag->addr = mlx_get_data_addr(bag->img, &bag->bits_per_pixel,
			&bag->line_length, &bag->endian);
}

void	init_game(t_bag *bag)
{
	int	i;
	int	j;

	bag->map.width = 50;
	bag->map.height = 50;
	bag->map.map = malloc(sizeof(char *) * bag->map.height);
	load_texture(bag, 0, "path/to/wall1.xpm");
	load_texture(bag, 1, "path/to/wall2.xpm");
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
				bag->map.map[i][j] = '0';
			j++;
		}
		i++;
	}
	init2(bag);
}
