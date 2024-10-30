/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmathis <dmathis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:31:40 by dmathis           #+#    #+#             */
/*   Updated: 2024/10/30 01:04:41 by dmathis          ###   ########.fr       */
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

int	game_loop(t_bag *game)
{
	static int	frame = 0;

	// Debug info
	if (frame++ % 60 == 0) // Print every 60 frames
	{
		printf("Camera pos: (%f, %f)\n", game->camera.position.x,
			game->camera.position.y);
		printf("Camera dir: (%f, %f)\n", game->camera.direction.x,
			game->camera.direction.y);
		printf("Camera plane: (%f, %f)\n", game->camera.plane.x,
			game->camera.plane.y);
	}
	// Clear screen
	ft_memset(game->addr, 0, SCREEN_WIDTH * SCREEN_HEIGHT
		* (game->bits_per_pixel / 8));
	// Draw ceiling
	for (int y = 0; y < SCREEN_HEIGHT / 2; y++)
		for (int x = 0; x < SCREEN_WIDTH; x++)
			my_mlx_pixel_put(game, x, y, game->map.ceiling_color);
	// Draw floor
	for (int y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y++)
		for (int x = 0; x < SCREEN_WIDTH; x++)
			my_mlx_pixel_put(game, x, y, game->map.floor_color);
	// Cast rays and draw walls
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_bag	game;

	printf("Initializing structures...\n");
	ft_struct_init(&game);
	printf("Starting parsing...\n");
	ft_parsing(argc, argv, &game);
	if (!game.map.is_map_valid)
	{
		ft_free_map(&game);
		return (-1);
	}
	ft_init_player(&game);
	if (game.map.player_x == -1 || game.map.player_y == -1)
	{
		printf("Error: Player position not initialized\n");
		ft_free_map(&game);
		return (1);
	}
	printf("Map valid, player position: (%d, %d) facing %c\n",
		game.map.player_x, game.map.player_y, game.map.player_dir);
	printf("Map successfully parsed.\n");
	printf("Initializing MLX...\n");
	if (!ft_init_mlx(&game))
	{
		ft_error_map("Failed to initialize MLX", &game);
		ft_cleanup(&game);
		return (1);
	}
	printf("Loading textures...\n");
	printf("NO texture path: %s\n", game.map.no_texture); // Debug
	printf("SO texture path: %s\n", game.map.so_texture); // Debug
	printf("WE texture path: %s\n", game.map.we_texture); // Debug
	printf("EA texture path: %s\n", game.map.ea_texture); // Debug
	if (!ft_load_all_textures(&game))
	{
		ft_cleanup(&game);
		return (1);
	}
	printf("Setting up game hooks...\n");
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, key_press, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	printf("Starting game loop...\n");
	mlx_loop(game.mlx);
	ft_cleanup(&game);
	return (0);
}
