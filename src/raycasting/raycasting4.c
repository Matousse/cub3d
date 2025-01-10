/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:56:39 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/10 00:56:50 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calc_texture_x(t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x * TEX_WIDTH);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
}

t_texture	*select_texture(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&game->textures.east);
		else
			return (&game->textures.west);
	}
	else
	{
		if (ray->dir_y > 0)
			return (&game->textures.south);
		else
			return (&game->textures.north);
	}
}
