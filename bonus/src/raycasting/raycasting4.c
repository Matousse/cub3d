/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 00:56:39 by dmathis           #+#    #+#             */
/*   Updated: 2025/01/10 06:00:00 by dmathis          ###   ########.fr       */
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

t_texture	*select_special_texture(t_ray *ray, t_game *game)
{
	int	frame;

	if (game->map.fullmap[ray->map_x][ray->map_y] == 'D')
		return (&game->textures.door);
	if (game->map.fullmap[ray->map_x][ray->map_y] == 'T')
	{
		frame = (game->animation.frame_count / 75) % 4;
		if (frame == 0)
			return (&game->textures.east);
		else if (frame == 1 && game->textures.wallsmiley1.img)
			return (&game->textures.wallsmiley1);
		else if (frame == 2)
			return (&game->textures.east);
		else if (frame == 3 && game->textures.wallsmiley2.img)
			return (&game->textures.wallsmiley2);
		return (&game->textures.east);
	}
	return (NULL);
}

t_texture	*select_texture(t_ray *ray, t_game *game)
{
	t_texture	*special;

	special = select_special_texture(ray, game);
	if (special)
		return (special);
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&game->textures.east);
		return (&game->textures.west);
	}
	if (ray->dir_y > 0)
		return (&game->textures.south);
	return (&game->textures.north);
}

int	is_door_open(t_game *game, int x, int y)
{
	int	i;

	if (!game || !game->map.doors || game->map.nb_doors <= 0)
		return (0);
	if (x < 0 || y < 0 || !game->map.fullmap[x]
		|| y >= ft_strlen(game->map.fullmap[x]))
		return (0);
	i = 0;
	while (i < game->map.nb_doors)
	{
		if (game->map.doors[i].x == x && game->map.doors[i].y == y)
		{
			if (game->map.doors[i].state == DOOR_OPEN)
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}
