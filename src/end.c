/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:59:16 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/21 16:14:00 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_bag *bag)
{
	int	i;

	i = 0;
	while (i < bag->map.height)
	{
		free(bag->map.map[i]);
		i++;
	}
	free(bag->map.map);
	mlx_destroy_image(bag->mlx, bag->img);
	mlx_destroy_window(bag->mlx, bag->win);
	mlx_destroy_display(bag->mlx);
	free(bag->mlx);
	exit(0);
	return (0);
}
