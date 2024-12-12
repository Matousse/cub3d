#include "../includes/cub3d.h"

void destroy_textures(t_game *game)
{
    if (game->textures.north.img)
        mlx_destroy_image(game->mlx, game->textures.north.img);
    if (game->textures.south.img)
        mlx_destroy_image(game->mlx, game->textures.south.img);
    if (game->textures.east.img)
        mlx_destroy_image(game->mlx, game->textures.east.img);
    if (game->textures.west.img)
        mlx_destroy_image(game->mlx, game->textures.west.img);
}

void cleanup_game(t_game *game)
{
    if (game)
    {
        // Libérer les textures
        destroy_textures(game);

        // Libérer la carte
        if (game->map)
        {
            for (int i = 0; i < game->map_height; i++)
            {
                if (game->map[i])
                    free(game->map[i]);
            }
            free(game->map);
            game->map = NULL;
        }

        // Libérer l'image principale
        if (game->img)
            mlx_destroy_image(game->mlx, game->img);

        // Détruire la fenêtre
        if (game->win)
            mlx_destroy_window(game->mlx, game->win);

        // Détruire le contexte MLX
        if (game->mlx)
        {
            mlx_destroy_display(game->mlx);
            free(game->mlx);
        }
    }
}

int close_window(t_game *game)
{
    cleanup_game(game);
    exit(0);
    return (0);
}