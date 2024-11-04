/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:56:30 by dmathis           #+#    #+#             */
/*   Updated: 2024/11/04 09:39:50 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_struct_init(t_bag *game)
{
	printf("Initializing game structure...\n");
	// MLX
	game->mlx = NULL;
	game->win = NULL;
	game->db_buff_img = NULL;
	game->buff_addr = NULL;
	// Map
	game->map.width = 0;
	game->map.height = 0;
	game->map.fullmap = NULL;
	game->map.no_texture = NULL;
	game->map.so_texture = NULL;
	game->map.we_texture = NULL;
	game->map.ea_texture = NULL;
	game->map.floor_color = 0;
	game->map.ceiling_color = 0;
	game->map.player_x = -1;
	game->map.player_y = -1;
	game->map.player_dir = '\0';
	game->map.is_map_valid = 0;
	game->map.all_info = 0;
	// Textures
	game->no_texture.img = NULL;
	game->so_texture.img = NULL;
	game->we_texture.img = NULL;
	game->ea_texture.img = NULL;
	// Camera
	game->camera.move_speed = 0.05;
	game->camera.rot_speed = 0.03;
	printf("Game structure initialized\n");
}

int	ft_init_mlx(t_bag *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
		return (0);
	game->db_buff_img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->db_buff_img)
		return (0);//Leak sur game->win si celui-ci échoue
	game->buff_addr = mlx_get_data_addr(game->db_buff_img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	if (!game->buff_addr)
		return (0);//Même chose mais pour les 2 du dessus.
	return (1);
}

void	ft_init_camera(t_bag *game)
{
	game->camera.position = (t_vector){game->map.player_x + 0.5,
		game->map.player_y + 0.5};
	game->camera.move_speed = 0.05;
	game->camera.rot_speed = 0.03;
	if (game->map.player_dir == 'N')
	{
		game->camera.direction.x = 0;
		game->camera.direction.y = -1;
		game->camera.plane.x = 0.66;
		game->camera.plane.y = 0;
	}
	else if (game->map.player_dir == 'S')
	{
		game->camera.direction.x = 0;
		game->camera.direction.y = 1;
		game->camera.plane.x = -0.66;
		game->camera.plane.y = 0;
	}
	else if (game->map.player_dir == 'E')
	{
		game->camera.direction.x = 1;
		game->camera.direction.y = 0;
		game->camera.plane.x = 0;
		game->camera.plane.y = 0.66;
	}
	else if (game->map.player_dir == 'W')
	{
		game->camera.direction.x = -1;
		game->camera.direction.y = 0;
		game->camera.plane.x = 0;
		game->camera.plane.y = -0.66;
	}
	printf("Camera initialized:\n");
	printf("Position: (%f, %f)\n", game->camera.position.x,
		game->camera.position.y);
	printf("Direction: (%f, %f)\n", game->camera.direction.x,
		game->camera.direction.y);
	printf("Plane: (%f, %f)\n", game->camera.plane.x, game->camera.plane.y);
}

void	ft_init_ray(t_bag *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->dir.x = game->camera.direction.x + game->camera.plane.x * camera_x;
	ray->dir.y = game->camera.direction.y + game->camera.plane.y * camera_x;
	ray->map_x = (int)game->camera.position.x;
	ray->map_y = (int)game->camera.position.y;
	// Nouveau calcul des delta_dist (plus besoin de vérifier dir.x/y == 0)
	ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	ray->delta_dist.y = fabs(1.0 / ray->dir.y);
	if (ray->dir.x == 0.0)
		ray->delta_dist.x = 1e30;
	if (ray->dir.y == 0.0)
		ray->delta_dist.y = 1e30;
	ray->hit = 0;
}
