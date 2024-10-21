/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:29:20 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/21 23:40:15 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_bag *bag, int x, int y, int color)
{
	char	*dst;

	dst = bag->addr + (y * bag->line_length + x * (bag->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	calculate_ray_dir(t_bag *bag, int x, t_vector *ray_dir)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray_dir->x = bag->camera.direction.x + bag->camera.plane.x * camera_x;
	ray_dir->y = bag->camera.direction.y + bag->camera.plane.y * camera_x;
}

void	init_dda(t_bag *bag, t_vector *ray_dir, t_vector *side_dist,
		t_vector *delta_dist)
{
	delta_dist->x = fabs(1 / ray_dir->x);
	delta_dist->y = fabs(1 / ray_dir->y);
	side_dist->x = (ray_dir->x < 0) ? (bag->camera.position.x
			- (int)bag->camera.position.x)
		* delta_dist->x : ((int)bag->camera.position.x + 1.0
			- bag->camera.position.x) * delta_dist->x;
	side_dist->y = (ray_dir->y < 0) ? (bag->camera.position.y
			- (int)bag->camera.position.y)
		* delta_dist->y : ((int)bag->camera.position.y + 1.0
			- bag->camera.position.y) * delta_dist->y;
}

int	perform_dda(t_bag *bag, t_vector *ray_dir, t_vector *side_dist,	t_vector *delta_dist)
{
	int	map_x;
	int	map_y;
	int	hit;
	int	side;

	map_x = (int)bag->camera.position.x;
	map_y = (int)bag->camera.position.y;
	hit = 0;
	while (hit == 0)
	{
		if (side_dist->x < side_dist->y)
		{
			side_dist->x += delta_dist->x;
			map_x += (ray_dir->x < 0) ? -1 : 1;
			side = 0;
		}
		else
		{
			side_dist->y += delta_dist->y;
			map_y += (ray_dir->y < 0) ? -1 : 1;
			side = 1;
		}
		if (bag->map.map[map_y][map_x] == '1')
			hit = 1;
	}
	return (side);
}

double	calculate_perp_wall_dist(t_bag *bag, t_vector *ray_dir, int side, int map_x, int map_y)
{
	double	perp_wall_dist;

	if (side == 0)
		perp_wall_dist = (map_x - bag->camera.position.x + (1
					- (ray_dir->x < 0 ? -1 : 1)) / 2) / ray_dir->x;
	else
		perp_wall_dist = (map_y - bag->camera.position.y + (1
					- (ray_dir->y < 0 ? -1 : 1)) / 2) / ray_dir->y;
	return (perp_wall_dist);
}

void	draw_vertical_line(t_bag *bag, int x, int draw_start, int draw_end,	int color)
{
	int	y;

	y = draw_start;
	while (y < draw_end)
	{
		my_mlx_pixel_put(bag, x, y, color);
		y++;
	}
}

void	cast_single_ray(t_bag *bag, int x)
{
	double	perp_wall_dist;
	int		color;

	t_vector ray_dir;
	t_vector side_dist;
	t_vector delta_dist;

	int side, line_height, draw_start, draw_end;
	calculate_ray_dir(bag, x, &ray_dir);
	init_dda(bag, &ray_dir, &side_dist, &delta_dist);
	side = perform_dda(bag, &ray_dir, &side_dist, &delta_dist);
	perp_wall_dist = calculate_perp_wall_dist(bag, &ray_dir, side,
			(int)(bag->camera.position.x + side_dist.x - delta_dist.x),
			(int)(bag->camera.position.y + side_dist.y - delta_dist.y));
	line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	color = (side == 1) ? 0x00FF00 : 0xFF0000;
	draw_vertical_line(bag, x, draw_start, draw_end, color);
}
void	cast_rays(t_bag *bag)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		cast_single_ray(bag, x);
		x++;
	}
	mlx_put_image_to_window(bag->mlx, bag->win, bag->img, 0, 0);
}

