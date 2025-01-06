#include "../../includes/cub3d.h"

void init_inventory(t_game *game)
{
    game->inventory.keys = 0;
    game->inventory.show_message = 0;
    game->inventory.message_timer = 0;
}

void collect_key(t_game *game, int map_x, int map_y)
{
    if (game->map.fullmap[map_x][map_y] == 'K')
    {
        game->inventory.keys++;
        game->map.fullmap[map_x][map_y] = '0';
    }
}

void try_open_door(t_game *game)
{
    int check_x = (int)(game->player.pos_x + game->player.dir_x);
    int check_y = (int)(game->player.pos_y + game->player.dir_y);

    if (check_x >= 0 && check_x < game->map.height && 
        check_y >= 0 && check_y < (int)ft_strlen(game->map.fullmap[check_x]))
    {
        if (game->map.fullmap[check_x][check_y] == 'D')
        {
            if (game->inventory.keys > 0)
            {
                game->map.fullmap[check_x][check_y] = '0';
                game->inventory.keys--;
            }
            else
            {
                game->inventory.show_message = 1;
                game->inventory.message_timer = MESSAGE_DURATION;
            }
        }
    }
}

void draw_inventory(t_game *game)
{
    if (game->inventory.keys > 0)
    {
        int key_x = 20;
        int key_y = WINDOW_HEIGHT - 70;
        mlx_put_image_to_window(game->mlx, game->win, 
            game->textures.key.img, key_x, key_y);
    }

    if (game->inventory.show_message && game->inventory.message_timer > 0)
    {
        mlx_string_put(game->mlx, game->win, 
            WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2, 
            0xFF0000, "Une cle est necessaire");
        
        game->inventory.message_timer--;
        if (game->inventory.message_timer <= 0)
            game->inventory.show_message = 0;
    }
}