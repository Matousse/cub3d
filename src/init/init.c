#include "../../includes/cub3d.h"

/* Initialisation */
void init_player_direction(t_game *game, char direction)
{
	printf("Setting player direction: %c\n", direction);

	game->move_forward = 0;
	game->move_backward = 0;
	game->move_left = 0;
	game->move_right = 0;
	game->rotate_left = 0;
	game->rotate_right = 0;

	game->game_state = GAME_STATE_MENU;

	if (direction == 'N')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
	else if (direction == 'S')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = -0.66;
	}
	else if (direction == 'E')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
	else if (direction == 'W')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
	}
	printf("Player direction set to: dir_x=%f, dir_y=%f, plane_x=%f, plane_y=%f\n",
		   game->player.dir_x, game->player.dir_y, game->player.plane_x, game->player.plane_y);
}

void find_player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	printf("Searching for player position...\n");
	while (game->map.fullmap[i])
	{
		j = 0;
		while (game->map.fullmap[i][j])
		{
			printf("%c", game->map.fullmap[i][j]);  // Debug: afficher la carte
			if (game->map.fullmap[i][j] == 'N' || game->map.fullmap[i][j] == 'S' ||
				game->map.fullmap[i][j] == 'E' || game->map.fullmap[i][j] == 'W')
			{
				printf("\nFound player at position: %d, %d (symbol: %c)\n",
					   i, j, game->map.fullmap[i][j]);
				game->player.pos_x = i + 0.5;  // Centre le joueur dans la case
				game->player.pos_y = j + 0.5;
				init_player_direction(game, game->map.fullmap[i][j]);
				game->map.fullmap[i][j] = '0';  // Libère la case
				return;
			}
			j++;
		}
		i++;
		printf("\n");  // Debug: nouvelle ligne pour la carte
	}
	printf("Player position not found!\n");
}

void init_game(t_game *game)
{
	int bpp = 32;
	int size_line = WINDOW_WIDTH * 4;  // 4 octets par pixel
	int endian = 0;
	int	i;

	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error: mlx initialization failed\n");
		exit(1);
	}

	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!game->win)
	{
		printf("Error: window creation failed\n");
		exit(1);
	}

	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
	{
		printf("Error: image creation failed\n");
		mlx_destroy_window(game->mlx, game->win);
		exit(1);
	}

	game->addr = mlx_get_data_addr(game->img, &bpp, &size_line, &endian);
	if (!game->addr)
	{
		printf("Error: getting image address failed\n");
		mlx_destroy_image(game->mlx, game->img);
		mlx_destroy_window(game->mlx, game->win);
		exit(1);
	}

	game->bits_per_pixel = bpp;
	game->line_length = size_line;
	game->endian = endian;
	game->addr = mlx_get_data_addr(game->img, &bpp, &size_line, &endian);
	if (!game->addr)
	{
		printf("Error: getting image address failed\n");
		mlx_destroy_image(game->mlx, game->img);
		mlx_destroy_window(game->mlx, game->win);
		exit(1);
	}

	game->bits_per_pixel = bpp;
	game->line_length = size_line;
	game->endian = endian;

	if (!load_textures(game))
		ft_error_handling(game, "loading textures failed");

	find_player_position(game);
	init_minimap(game);
}
