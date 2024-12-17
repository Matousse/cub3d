#include "../../includes/cub3d.h"

void draw_text_center(t_game *game, char *text, int y, int color)
{
    int text_width = ft_strlen(text) * 10;  // Estimation approximative
    int x = (WINDOW_WIDTH - text_width) / 2;
    mlx_string_put(game->mlx, game->win, x, y, color, text);
}

void draw_menu(t_game *game)
{
    // Fond noir
    for (int y = 0; y < WINDOW_HEIGHT; y++)
        for (int x = 0; x < WINDOW_WIDTH; x++)
            put_pixel(game, x, y, 0x000000);
            
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    draw_text_center(game, "JOUER", WINDOW_HEIGHT / 2, 0xFFFFFF);
    draw_text_center(game, "Appuyez sur ENTREE pour commencer", 
                    WINDOW_HEIGHT / 2 + 40, 0xFFFFFF);
}

void draw_gameover(t_game *game)
{
    // Fond semi-transparent
    for (int y = 0; y < WINDOW_HEIGHT; y++)
        for (int x = 0; x < WINDOW_WIDTH; x++)
        {
            int current = *(unsigned int*)(game->addr + 
                (y * game->line_length + x * (game->bits_per_pixel / 8)));
            int blended = ((current & 0xFEFEFE) >> 1) | 0x800000;
            put_pixel(game, x, y, blended);
        }
    
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    draw_text_center(game, "PERDU", WINDOW_HEIGHT / 2, 0xFF0000);
}

void draw_timer(t_game *game)
{
    int remaining = INITIAL_TIME - (game->current_time - game->start_time);
    if (remaining < 0) remaining = 0;
    
    char timer_text[6];
    snprintf(timer_text, 6, "%02d:%02d", remaining / 60, remaining % 60);
    
    // Position en bas à droite avec une marge de 20 pixels
    int x = WINDOW_WIDTH - 120; 
    int y = WINDOW_HEIGHT - 40;
    
    // et couleur rouge (0xFF0000)
    mlx_string_put(game->mlx, game->win, x, y, 0xFF0000, timer_text);
}