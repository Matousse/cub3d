/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:29:20 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/29 16:09:54 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

int	perform_dda(t_bag *bag, t_vector *ray_dir, t_vector *side_dist,
		t_vector *delta_dist)
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
		// Vérification des limites de la carte
		if (map_y < 0 || map_y >= bag->map.height || map_x < 0
			|| map_x >= bag->map.width)
			break ;
		// Utilisation de fullmap au lieu de map
		if (bag->map.fullmap[map_y][map_x] == '1')
			hit = 1;
	}
	return (side);
}

double	calculate_perp_wall_dist(t_bag *bag, t_vector *ray_dir, int side,
		int map_x, int map_y)
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

void	draw_vertical_line(t_bag *bag, int x, int draw_start, int draw_end,
		int color)
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
	t_ray_info	ray;

	// Calculate ray direction
	calculate_ray_dir(bag, x, &ray.dir);
	// Initialize DDA
	init_dda(bag, &ray.dir, &ray.side_dist, &ray.delta_dist);
	// Perform DDA
	ray.side = perform_dda(bag, &ray.dir, &ray.side_dist, &ray.delta_dist);
	// Calculate distance to wall
	ray.perp_wall_dist = calculate_perp_wall_dist(bag, &ray.dir, ray.side,
			(int)(bag->camera.position.x + ray.side_dist.x - ray.delta_dist.x),
			(int)(bag->camera.position.y + ray.side_dist.y - ray.delta_dist.y));
	// Calculate wall height and drawing boundaries
	ray.line_height = (int)(SCREEN_HEIGHT / ray.perp_wall_dist);
	ray.draw_start = -ray.line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray.draw_start < 0)
		ray.draw_start = 0;
	ray.draw_end = ray.line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray.draw_end >= SCREEN_HEIGHT)
		ray.draw_end = SCREEN_HEIGHT - 1;
	// Draw the textured wall slice
	draw_textured_line(bag, x, &ray);
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
unsigned int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;

	if (tex_x < 0)
		tex_x = 0;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	pixel = texture->addr + (tex_y * texture->line_length + tex_x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

void	draw_textured_line(t_bag *bag, int x, t_ray_info *ray)
{
	double			step;
	double			tex_pos;
	int				y;
	t_texture		*current_texture;
	unsigned int	color;
	double			wall_x;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	int tex_x, tex_y;
	// Calculate texture X coordinate
	if (ray->side == 0)
		wall_x = bag->camera.position.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = bag->camera.position.x + ray->perp_wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	// Select texture based on wall orientation
	if (ray->side == 0 && ray->dir.x > 0)
		current_texture = &bag->ea_texture;
	else if (ray->side == 0)
		current_texture = &bag->we_texture;
	else if (ray->dir.y > 0)
		current_texture = &bag->so_texture;
	else
		current_texture = &bag->no_texture;
	// Calculate texture X coordinate
	tex_x = (int)(wall_x * current_texture->width);
	if ((ray->side == 0 && ray->dir.x < 0) || (ray->side == 1
			&& ray->dir.y < 0))
		tex_x = current_texture->width - tex_x - 1;
	// Calculate texture step and starting position
	step = 1.0 * current_texture->height / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2)
		* step;
	// Draw the vertical textured line
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (current_texture->height - 1);
		tex_pos += step;
		color = get_texture_color(current_texture, tex_x, tex_y);
		// Apply shading based on distance
		if (ray->side == 1)
		{
			r = (color >> 16) & 0xFF;
			g = (color >> 8) & 0xFF;
			b = color & 0xFF;
			r = r * 0.7;
			g = g * 0.7;
			b = b * 0.7;
			color = (r << 16) | (g << 8) | b;
		}
		my_mlx_pixel_put(bag, x, y, color);
		y++;
	}
}
