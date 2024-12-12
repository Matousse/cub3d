//pixels.c

#include "../../includes/cub3d.h"

/* Fonction pour obtenir la couleur d'un pixel dans une texture */
int get_texture_color(t_texture *texture, int x, int y)
{
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return (0);
    return (texture->data[y * texture->width + x]);
}

/* Fonction pour mettre un pixel dans l'image */
void put_pixel(t_game *game, int x, int y, int color)
{
    char *dst;

    if (!game || !game->addr || x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return;

    // Calculer l'offset en octets
    long offset = y * game->line_length + x * (game->bits_per_pixel / 8);
    
    // Vérifier que l'offset ne dépasse pas la taille de l'image
    if (offset >= WINDOW_WIDTH * WINDOW_HEIGHT * (game->bits_per_pixel / 8))
        return;

    dst = game->addr + offset;
    *(unsigned int*)dst = color;
}