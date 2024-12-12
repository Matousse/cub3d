#include "../../includes/cub3d.h"

/* Initialisation */
void init_player_direction(t_game *game, char direction)
{
    printf("Setting player direction: %c\n", direction);
    
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
    printf("Searching for player position...\n");
    for (int i = 0; i < game->map_height; i++)
    {
        for (int j = 0; j < game->map_width; j++)
        {
            printf("%c", game->map[i][j]);  // Debug: afficher la carte
            if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
                game->map[i][j] == 'E' || game->map[i][j] == 'W')
            {
                printf("\nFound player at position: %d, %d (symbol: %c)\n", 
                       i, j, game->map[i][j]);
                game->player.pos_x = i + 0.5;  // Centre le joueur dans la case
                game->player.pos_y = j + 0.5;
                init_player_direction(game, game->map[i][j]);
                game->map[i][j] = '0';  // Libère la case
                return;
            }
        }
        printf("\n");  // Debug: nouvelle ligne pour la carte
    }
    printf("Player position not found!\n");
}

void init_game(t_game *game)
{
    int bpp = 32;
    int size_line = WINDOW_WIDTH * 4;  // 4 octets par pixel
    int endian = 0;

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

    /* Initialisation de la carte */
    game->map_width = 8;
    game->map_height = 8;
    game->map = malloc(sizeof(char *) * game->map_height);
    if (!game->map)
    {
        printf("Error: map allocation failed\n");
        mlx_destroy_image(game->mlx, game->img);
        mlx_destroy_window(game->mlx, game->win);
        exit(1);
    }

    for (int i = 0; i < game->map_height; i++)
    {
        game->map[i] = malloc(sizeof(char) * game->map_width);
        if (!game->map[i])
        {
            printf("Error: map row allocation failed\n");
            // Libérer les lignes précédentes
            for (int j = 0; j < i; j++)
                free(game->map[j]);
            free(game->map);
            mlx_destroy_image(game->mlx, game->img);
            mlx_destroy_window(game->mlx, game->win);
            exit(1);
        }
        for (int j = 0; j < game->map_width; j++)
            game->map[i][j] = default_map[i][j];
    }

    if (!load_textures(game))
    {
        printf("Error: loading textures failed\n");
        // Libérer la carte
        for (int i = 0; i < game->map_height; i++)
            free(game->map[i]);
        free(game->map);
        mlx_destroy_image(game->mlx, game->img);
        mlx_destroy_window(game->mlx, game->win);
        exit(1);
    }

    find_player_position(game);
}