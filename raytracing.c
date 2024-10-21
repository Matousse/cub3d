/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:29:20 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/21 14:31:22 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_ray(Map *map, Camera *camera, int x, int y, int *texture_id,
		double *distance)
{
	double		ray_angle;
	Vector2D	ray_dir;
	Vector2D	ray_unit_step;
	Vector2D	ray_length;
	Vector2D	step;
	Vector2D	map_check;
	double		max_distance;
	double		distance_traveled;
	bool		hit_wall;

	ray_angle = camera->direction.x - camera->fov / 2.0 + camera->fov * x
		/ map->width;
	ray_dir = {cos(ray_angle), sin(ray_angle)};
	ray_unit_step = {sqrt(1 + (ray_dir.y / ray_dir.x) * (ray_dir.y
				/ ray_dir.x)), sqrt(1 + (ray_dir.x / ray_dir.y) * (ray_dir.x
				/ ray_dir.y))};
	map_check = {floor(camera->position.x), floor(camera->position.y)};
	if (ray_dir.x < 0)
	{
		step.x = -1;
		ray_length.x = (camera->position.x - map_check.x) * ray_unit_step.x;
	}
	else
	{
		step.x = 1;
		ray_length.x = (map_check.x + 1.0 - camera->position.x)
			* ray_unit_step.x;
	}
	if (ray_dir.y < 0)
	{
		step.y = -1;
		ray_length.y = (camera->position.y - map_check.y) * ray_unit_step.y;
	}
	else
	{
		step.y = 1;
		ray_length.y = (map_check.y + 1.0 - camera->position.y)
			* ray_unit_step.y;
	}
	max_distance = 100.0;
	distance_traveled = 0;
	hit_wall = false;
	while (!hit_wall && distance_traveled < max_distance)
	{
		if (ray_length.x < ray_length.y)
		{
			map_check.x += step.x;
			distance_traveled = ray_length.x;
			ray_length.x += ray_unit_step.x;
		}
		else
		{
			map_check.y += step.y;
			distance_traveled = ray_length.y;
			ray_length.y += ray_unit_step.y;
		}
		if (map_check.x >= 0 && map_check.x < map->width && map_check.y >= 0
			&& map_check.y < map->height)
		{
			if (map->map[(int)map_check.y][(int)map_check.x] != '0')
			{
				hit_wall = true;
				*texture_id = map->map[(int)map_check.y][(int)map_check.x]
					- '0';
			}
		}
	}
	*distance = distance_traveled;
}

void	render_frame(Map *map, Camera *camera)
{
		int texture_id;
		double distance;

	for (int x = 0; x < map->width; x++)
	{
		cast_ray(map, camera, x, 0, &texture_id, &distance);
	}
}
