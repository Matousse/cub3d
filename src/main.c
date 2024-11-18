/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dloisel <dloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:31:40 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/31 15:52:58 by dloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_bag *bag)
{
	double	oldDirX;
	double	oldPlaneX;

	printf("Key pressed: %d\n", keycode);
	if (keycode == KEY_ESC)
		close_window(bag);
	if (keycode == KEY_W)
	{
		bag->camera.position.x += bag->camera.direction.x * MOVE_SPEED;
		bag->camera.position.y += bag->camera.direction.y * MOVE_SPEED;
	}
	if (keycode == KEY_S)
	{
		bag->camera.position.x -= bag->camera.direction.x * MOVE_SPEED;
		bag->camera.position.y -= bag->camera.direction.y * MOVE_SPEED;
	}
	if (keycode == KEY_A)
	{
		oldDirX = bag->camera.direction.x;
		bag->camera.direction.x = bag->camera.direction.x * cos(-ROTATE_SPEED)
			- bag->camera.direction.y * sin(-ROTATE_SPEED);
		bag->camera.direction.y = oldDirX * sin(-ROTATE_SPEED)
			+ bag->camera.direction.y * cos(-ROTATE_SPEED);
		oldPlaneX = bag->camera.plane.x;
		bag->camera.plane.x = bag->camera.plane.x * cos(-ROTATE_SPEED)
			- bag->camera.plane.y * sin(-ROTATE_SPEED);
		bag->camera.plane.y = oldPlaneX * sin(-ROTATE_SPEED)
			+ bag->camera.plane.y * cos(-ROTATE_SPEED);
	}
	if (keycode == KEY_D)
	{
		oldDirX = bag->camera.direction.x;
		bag->camera.direction.x = bag->camera.direction.x * cos(ROTATE_SPEED)
			- bag->camera.direction.y * sin(ROTATE_SPEED);
		bag->camera.direction.y = oldDirX * sin(ROTATE_SPEED)
			+ bag->camera.direction.y * cos(ROTATE_SPEED);
		oldPlaneX = bag->camera.plane.x;
		bag->camera.plane.x = bag->camera.plane.x * cos(ROTATE_SPEED)
			- bag->camera.plane.y * sin(ROTATE_SPEED);
		bag->camera.plane.y = oldPlaneX * sin(ROTATE_SPEED)
			+ bag->camera.plane.y * cos(ROTATE_SPEED);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_bag	*game;

	game = malloc(sizeof(t_bag));
	if (!game)
		return (1);
	printf("Starting program...\n");
	ft_struct_init(game);
	printf("Structures initialized\n");
	printf("Starting parsing...\n");
	ft_parsing(argc, argv, game);
	printf("Parsing successful\n");
	printf("Initializing player...\n");
	ft_init_player(game);
	printf("Player initialized at pos: (%d, %d) facing %c\n", game->map.player_x,
		game->map.player_y, game->map.player_dir);
	printf("Initializing MLX...\n");
	ft_init_mlx(game);
	printf("MLX initialized\n");
	printf("Loading textures...\n");
	ft_init_texture(game);
	printf("Textures loaded\n");
	printf("Setting up hooks...\n");
	ft_setup_hooks(game);
	printf("Hooks set up\n");
	printf("Starting game loop...\n");
	mlx_loop(game->mlx);
	return (0);
}
