/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:56:30 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/29 16:54:10 by dmathis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_get_player_pos(t_bag *game)
{
	int	i;
	int	j;

	i = 0;
	if (!game || !game->map.fullmap)
	{
		printf("Error: null map in ft_get_player_pos\n");
		return ;
	}
	printf("Starting player position search...\n");
	while (game->map.fullmap[i])
	{
		j = 0;
		printf("Checking line %d: %s\n", i, game->map.fullmap[i]);
		while (game->map.fullmap[i][j])
		{
			if (game->map.fullmap[i][j] == 'N' || game->map.fullmap[i][j] == 'S'
				|| game->map.fullmap[i][j] == 'E'
				|| game->map.fullmap[i][j] == 'W')
			{
				game->map.player_x = j;
				game->map.player_y = i;
				game->map.player_dir = game->map.fullmap[i][j];
				printf("Player found at: (%d, %d) facing %c\n", j, i,
					game->map.fullmap[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	ft_struct_init(t_bag *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->addr = NULL;
	game->bits_per_pixel = 0;
	game->line_length = 0;
	game->endian = 0;
	// Map initialization
	game->map.fullmap = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.no_texture = NULL;
	game->map.so_texture = NULL;
	game->map.we_texture = NULL;
	game->map.ea_texture = NULL;
	game->map.floor_color = 0;
	game->map.ceiling_color = 0;
	game->map.is_map_valid = 0;
	game->map.all_info = 0;
	game->map.player_x = -1;  // Ajout d'une valeur par défaut
	game->map.player_y = -1;  // Ajout d'une valeur par défaut
	game->map.player_dir = 0; // Ajout d'une valeur par défaut
	// Initialize textures
	game->no_texture.img = NULL;
	game->so_texture.img = NULL;
	game->we_texture.img = NULL;
	game->ea_texture.img = NULL;
	// Initialize camera
	game->camera.position.x = 0;
	game->camera.position.y = 0;
	game->camera.direction.x = 0;
	game->camera.direction.y = 0;
	game->camera.plane.x = 0;
	game->camera.plane.y = 0;
	game->camera.fov = 60 * M_PI / 180;
}

int	ft_init_mlx(t_bag *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!game->win)
		return (0);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img)
		return (0);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	if (!game->addr)
		return (0);
	return (1);
}

void	ft_init_player(t_bag *game)
{
	printf("Initializing player...\n");
	printf("Player start position from map: (%d, %d)\n", game->map.player_x,
		game->map.player_y);
	printf("Player direction from map: %c\n", game->map.player_dir);
	// Vérification des valeurs
	if (game->map.player_x < 0 || game->map.player_y < 0
		|| !game->map.player_dir)
	{
		ft_error_map("Invalid player position or direction", game);
		return ;
	}
	// Set initial position
	game->camera.position.x = game->map.player_x + 0.5;
	game->camera.position.y = game->map.player_y + 0.5;
	// Set initial direction and plane based on player orientation
	switch (game->map.player_dir)
	{
	case 'N':
		game->camera.direction = (t_vector){0, -1};
		game->camera.plane = (t_vector){0.66, 0};
		break ;
	case 'S':
		game->camera.direction = (t_vector){0, 1};
		game->camera.plane = (t_vector){-0.66, 0};
		break ;
	case 'E':
		game->camera.direction = (t_vector){1, 0};
		game->camera.plane = (t_vector){0, 0.66};
		break ;
	case 'W':
		game->camera.direction = (t_vector){-1, 0};
		game->camera.plane = (t_vector){0, -0.66};
		break ;
	default:
		ft_error_map("Invalid player direction", game);
		return ;
	}
	printf("Camera initialized at: (%f, %f)\n", game->camera.position.x,
		game->camera.position.y);
	printf("Camera direction: (%f, %f)\n", game->camera.direction.x,
		game->camera.direction.y);
	printf("Camera plane: (%f, %f)\n", game->camera.plane.x,
		game->camera.plane.y);
}
