#include "../../includes/cub3d.h"

/* Fonction pour charger une texture */
int load_texture(t_game *game, t_texture *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(game->mlx, path, 
                                        &texture->width, &texture->height);
    if (!texture->img)
        return (0);
    texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
                                            &texture->line_length, &texture->endian);
    return (1);
}

/* Fonction pour charger toutes les textures */
int load_textures(t_game *game)
{
    if (!load_texture(game, &game->textures.north, "./textures/north.xpm"))
        return (0);
    if (!load_texture(game, &game->textures.south, "./textures/south.xpm"))
        return (0);
    if (!load_texture(game, &game->textures.east, "./textures/east.xpm"))
        return (0);
    if (!load_texture(game, &game->textures.west, "./textures/west.xpm"))
        return (0);
    return (1);
}