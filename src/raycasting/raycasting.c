//raycasting.c

#include "../../includes/cub3d.h"

/* Fonction principale de raycasting avec textures */
#include "../../includes/cub3d.h"

/* Fonction principale de raycasting avec textures et brouillard */
void raycasting(t_game *game)
{
    for (int x = 0; x < WINDOW_WIDTH; x++)
    {
        // Calcul de la direction du rayon
        double camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
        double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
        double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

        // Position actuelle sur la carte
        int map_x = (int)game->player.pos_x;
        int map_y = (int)game->player.pos_y;

        // Longueur du rayon d'un côté à l'autre
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);

        // Variables pour l'algorithme DDA
        double side_dist_x;
        double side_dist_y;
        int step_x;
        int step_y;
        int hit = 0;
        int side;

        // Calcul du pas et de la distance initiale
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (game->player.pos_x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->player.pos_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (game->player.pos_y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->player.pos_y) * delta_dist_y;
        }

        // Algorithme DDA (Digital Differential Analysis)
        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }

            // Vérification des limites de la carte
            if (map_x < 0 || map_x >= game->map.height || map_y < 0)
                break;

            // Vérification de la longueur de la ligne actuelle
            size_t row_length = ft_strlen(game->map.fullmap[map_x]);
            if (map_y >= row_length)
                break;

            // Vérification de collision avec un mur
            if (game->map.fullmap[map_x][map_y] == '1')
                hit = 1;
        }

        // Calcul de la distance au mur (perpendiculaire)
        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = (map_x - game->player.pos_x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - game->player.pos_y + (1 - step_y) / 2) / ray_dir_y;

        // Application du brouillard basé sur la distance
        double fog_factor = 1.0;
        if (game->fog_level > 0)
        {
            fog_factor = 1.0 - (perp_wall_dist / game->view_distance);
            if (fog_factor < 0)
                fog_factor = 0;
            if (fog_factor > 1)
                fog_factor = 1;
        }

        // Calcul de la hauteur du mur à l'écran
        int line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);

        // Calcul des pixels le plus bas et le plus haut à remplir
        int draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_end >= WINDOW_HEIGHT)
            draw_end = WINDOW_HEIGHT - 1;

        // Calcul de la coordonnée x du mur (pour la texture)
        double wall_x;
        if (side == 0)
            wall_x = game->player.pos_y + perp_wall_dist * ray_dir_y;
        else
            wall_x = game->player.pos_x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);

        // Calcul des coordonnées de texture
        int tex_x = (int)(wall_x * TEX_WIDTH);
        if (side == 0 && ray_dir_x > 0)
            tex_x = TEX_WIDTH - tex_x - 1;
        if (side == 1 && ray_dir_y < 0)
            tex_x = TEX_WIDTH - tex_x - 1;

        // Sélection de la texture selon le côté du mur
        t_texture *texture;
        if (side == 0)
            texture = ray_dir_x > 0 ? &game->textures.east : &game->textures.west;
        else
            texture = ray_dir_y > 0 ? &game->textures.south : &game->textures.north;

        // Calcul du pas de texture et de la position de départ
        double step = 1.0 * TEX_HEIGHT / line_height;
        double tex_pos = (draw_start - WINDOW_HEIGHT / 2 + line_height / 2) * step;

        // Dessin du mur texturé avec brouillard
        for (int y = draw_start; y < draw_end; y++)
        {
            int tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
            tex_pos += step;

            int color = get_texture_color(texture, tex_x, tex_y);

            // Assombrir les côtés y
            if (side == 1)
                color = (color >> 1) & 0x7F7F7F;

            // Appliquer le brouillard
            if (game->fog_level > 0)
            {
                int fog_color = 0x808080;  // Couleur grise du brouillard
                int r = ((color & 0xFF0000) >> 16) * fog_factor + ((fog_color & 0xFF0000) >> 16) * (1 - fog_factor);
                int g = ((color & 0x00FF00) >> 8) * fog_factor + ((fog_color & 0x00FF00) >> 8) * (1 - fog_factor);
                int b = (color & 0x0000FF) * fog_factor + (fog_color & 0x0000FF) * (1 - fog_factor);
                color = (r << 16) | (g << 8) | b;
            }

            put_pixel(game, x, y, color);
        }

        // Distance de brouillard pour le sol et le plafond
        double floor_fog_start = game->view_distance * 0.5;  // Le brouillard commence à mi-chemin

        // Dessin du plafond avec brouillard
        for (int y = 0; y < draw_start; y++)
        {
            double ray_dir_x0 = game->player.dir_x - game->player.plane_x;
            double ray_dir_y0 = game->player.dir_y - game->player.plane_y;
            double ray_dir_x1 = game->player.dir_x + game->player.plane_x;
            double ray_dir_y1 = game->player.dir_y + game->player.plane_y;

            int p = y - WINDOW_HEIGHT / 2;
            double pos_z = 0.5 * WINDOW_HEIGHT;
            double row_distance = pos_z / p;

            double floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / WINDOW_WIDTH;
            double floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / WINDOW_WIDTH;

            double floor_x = game->player.pos_x + row_distance * ray_dir_x0;
            double floor_y = game->player.pos_y + row_distance * ray_dir_y0;

            int ceiling_color = 0x00AAAAAA;

            if (game->fog_level > 0 && row_distance > floor_fog_start)
            {
                double ceiling_fog = (row_distance - floor_fog_start) / (game->view_distance - floor_fog_start);
                if (ceiling_fog > 1) ceiling_fog = 1;
                int r = ((ceiling_color & 0xFF0000) >> 16) * (1 - ceiling_fog) + ((0x808080 & 0xFF0000) >> 16) * ceiling_fog;
                int g = ((ceiling_color & 0x00FF00) >> 8) * (1 - ceiling_fog) + ((0x808080 & 0x00FF00) >> 8) * ceiling_fog;
                int b = (ceiling_color & 0x0000FF) * (1 - ceiling_fog) + (0x808080 & 0x0000FF) * ceiling_fog;
                ceiling_color = (r << 16) | (g << 8) | b;
            }

            put_pixel(game, x, y, ceiling_color);
        }

        // Dessin du sol avec brouillard
        for (int y = draw_end; y < WINDOW_HEIGHT; y++)
        {
            double ray_dir_x0 = game->player.dir_x - game->player.plane_x;
            double ray_dir_y0 = game->player.dir_y - game->player.plane_y;
            double ray_dir_x1 = game->player.dir_x + game->player.plane_x;
            double ray_dir_y1 = game->player.dir_y + game->player.plane_y;

            int p = y - WINDOW_HEIGHT / 2;
            double pos_z = 0.5 * WINDOW_HEIGHT;
            double row_distance = pos_z / p;

            double floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / WINDOW_WIDTH;
            double floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / WINDOW_WIDTH;

            double floor_x = game->player.pos_x + row_distance * ray_dir_x0;
            double floor_y = game->player.pos_y + row_distance * ray_dir_y0;

            int floor_color = 0x00555555;

            if (game->fog_level > 0 && row_distance > floor_fog_start)
            {
                double floor_fog = (row_distance - floor_fog_start) / (game->view_distance - floor_fog_start);
                if (floor_fog > 1) floor_fog = 1;
                int r = ((floor_color & 0xFF0000) >> 16) * (1 - floor_fog) + ((0x808080 & 0xFF0000) >> 16) * floor_fog;
                int g = ((floor_color & 0x00FF00) >> 8) * (1 - floor_fog) + ((0x808080 & 0x00FF00) >> 8) * floor_fog;
                int b = (floor_color & 0x0000FF) * (1 - floor_fog) + (0x808080 & 0x0000FF) * floor_fog;
                floor_color = (r << 16) | (g << 8) | b;
            }

            put_pixel(game, x, y, floor_color);
        }
    }
}

/* Boucle de rendu */
int render(t_game *game)
{
    if (game->game_state == GAME_STATE_MENU)
    {
        draw_menu(game);
        return (0);
    }

    move_player(game);
    raycasting(game);

    // Appliquer le fog si nécessaire
    if (game->fog_intensity > 0)
    {
        for (int y = 0; y < WINDOW_HEIGHT; y++)
            for (int x = 0; x < WINDOW_WIDTH; x++)
            {
                int current = *(unsigned int*)(game->addr +
                    (y * game->line_length + x * (game->bits_per_pixel / 8)));
                int fog_color = 0x808080;  // Gris
                int fogged = current * (1 - game->fog_intensity) +
                            fog_color * game->fog_intensity;
                put_pixel(game, x, y, fogged);
            }
    }

    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

    update_game_state(game);
    draw_timer(game);
	update_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap->img, 10, 10);

    if (game->game_state == GAME_STATE_GAMEOVER)
        draw_gameover(game);

    return (0);
}

int blend_color(int color1, int color2, double factor)
{
    int r = ((color1 & 0xFF0000) >> 16) * factor + ((color2 & 0xFF0000) >> 16) * (1 - factor);
    int g = ((color1 & 0x00FF00) >> 8) * factor + ((color2 & 0x00FF00) >> 8) * (1 - factor);
    int b = (color1 & 0x0000FF) * factor + (color2 & 0x0000FF) * (1 - factor);
    return (r << 16) | (g << 8) | b;
}
