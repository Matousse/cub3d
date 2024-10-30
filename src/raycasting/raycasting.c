/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:29:20 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/30 03:43:30 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_game_loop(t_bag *game)
{
	ft_clear_image(game);
	ft_raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

void	ft_clear_image(t_bag *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			ft_put_pixel(game, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

void	ft_put_pixel(t_bag *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}

void	ft_raycasting(t_bag *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ft_init_ray(game, &ray, x);
		ft_calculate_step(game, &ray); // Ajout du paramètre game
		ft_perform_dda(game, &ray);
		ft_calculate_wall(game, &ray);
		ft_draw_wall(game, &ray, x);
		x++;
	}
}

void	ft_init_ray(t_bag *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->dir.x = game->camera.direction.x + game->camera.plane.x * camera_x;
	ray->dir.y = game->camera.direction.y + game->camera.plane.y * camera_x;
	ray->map_x = (int)game->camera.position.x;
	ray->map_y = (int)game->camera.position.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	ray->hit = 0;
}

void	ft_calculate_step(t_bag *game, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (game->camera.position.x - ray->map_x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - game->camera.position.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (game->camera.position.y - ray->map_y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - game->camera.position.y)
			* ray->delta_dist.y;
	}
}

void	ft_perform_dda(t_bag *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map.fullmap[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	ft_calculate_wall(t_bag *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->camera.position.x + (1
					- ray->step_x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map_y - game->camera.position.y + (1
					- ray->step_y) / 2) / ray->dir.y;
	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
}

void	ft_draw_wall(t_bag *game, t_ray *ray, int x)
{
	int	y;

	// Draw ceiling
	y = 0;
	while (y < ray->draw_start)
	{
		ft_put_pixel(game, x, y, game->map.ceiling_color);
		y++;
	}
	// Draw wall
	while (y < ray->draw_end)
	{
		ft_draw_texture(game, ray, x, y);
		y++;
	}
	// Draw floor
	while (y < WINDOW_HEIGHT)
	{
		ft_put_pixel(game, x, y, game->map.floor_color);
		y++;
	}
}
