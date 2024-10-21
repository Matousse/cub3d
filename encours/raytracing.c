/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:29:20 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/21 16:25:49 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_ray_dir(t_camera *cam, int x, t_vector *ray_dir)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray_dir->x = cam->direction.x + cam->plane.x * camera_x;
	ray_dir->y = cam->direction.y + cam->plane.y * camera_x;
}

void	init_dda(t_vector *ray_dir, t_vector *side_dist, t_vector *delta_dist,
		t_vector *map, t_camera *cam, int *step_x, int *step_y)
{
	delta_dist->x = fabs(1 / ray_dir->x);
	delta_dist->y = fabs(1 / ray_dir->y);
	map->x = (int)cam->position.x;
	map->y = (int)cam->position.y;
	if (ray_dir->x < 0)
	{
		*step_x = -1;
		side_dist->x = (cam->position.x - map->x) * delta_dist->x;
	}
	else
	{
		*step_x = 1;
		side_dist->x = (map->x + 1.0 - cam->position.x) * delta_dist->x;
	}
	if (ray_dir->y < 0)
	{
		*step_y = -1;
		side_dist->y = (cam->position.y - map->y) * delta_dist->y;
	}
	else
	{
		*step_y = 1;
		side_dist->y = (map->y + 1.0 - cam->position.y) * delta_dist->y;
	}
}

void	perform_dda(t_vector *map, t_vector *side_dist,
		t_vector *delta_dist, int *side, int step_x, int step_y)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (side_dist->x < side_dist->y)
		{
			side_dist->x += delta_dist->x;
			map->x += step_x;
			*side = 0;
		}
		else
		{
			side_dist->y += delta_dist->y;
			map->y += step_y;
			*side = 1;
		}
	}
}
/*ajouter ce merdier au dessus quand on a la map

		if (big_map[(int)map->x][(int)map->y] > 0)
			hit = 1;

			*/

double	calculate_wall_dist(t_vector *map, t_vector *ray_dir, int side,
		t_camera *cam, int step_x, int step_y)
{
	double	perp_wall_dist;

	if (side == 0)
		perp_wall_dist = (map->x - cam->position.x + (1 - step_x) / 2) / ray_dir->x;
	else
		perp_wall_dist = (map->y - cam->position.y + (1 - step_y) / 2) / ray_dir->y;
	return (perp_wall_dist);
}

void	draw_vertical_line(int draw_start, int draw_end)
{
	int	y;

	y = draw_start;
	while (y < draw_end)
	{
		y++;
	}
}

void	cast_rays(t_camera *cam)
{
	int		x;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int 	color;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		t_vector ray_dir, side_dist, delta_dist, map;
		int side, step_x, step_y;

		calculate_ray_dir(cam, x, &ray_dir);
		init_dda(&ray_dir, &side_dist, &delta_dist, &map, cam, &step_x,
			&step_y);
		perform_dda(&map, &ray_dir, &side_dist, &delta_dist, &side, step_x,
			step_y);
		perp_wall_dist = calculate_wall_dist(&map, &ray_dir, side, cam, step_x,
				step_y);
		line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
		if (side == 1)
			color = 0x00FF00;
		else
			color = 0xFF0000;
		draw_vertical_line(x, draw_start, draw_end, color);
		x++;
	}
}
