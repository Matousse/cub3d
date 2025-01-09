//hooks.c

#include "../../includes/cub3d.h"

/* Gestion des touches */
int key_press(int keycode, t_game *game)
{
    if (game->game_state == GAME_STATE_MENU && keycode == 65293) // Touche Entrée
    {
        game->game_state = GAME_STATE_PLAYING;
        game->start_time = time(NULL);
        return (0);
    }
    if (game->game_state != GAME_STATE_PLAYING)
        return (0);
	if (keycode == 65307)        /* ESC */
        close_window(game);
    else if (keycode == 119)     /* W */
        game->move_forward = 1;
    else if (keycode == 115)     /* S */
        game->move_backward = 1;
    else if (keycode == 100)     /* D */
        game->move_right = 1;
    else if (keycode == 97)      /* A */
        game->move_left = 1;
    return (0);
}

int key_release(int keycode, t_game *game)
{
    if (keycode == 119)          /* W */
        game->move_forward = 0;
    else if (keycode == 115)     /* S */
        game->move_backward = 0;
    else if (keycode == 100)     /* D */
        game->move_right = 0;
    else if (keycode == 97)      /* A */
        game->move_left = 0;
    return (0);
}

void move_player(t_game *game)
{
    // Gestion du mouvement avant/arrière
    if (game->move_forward)
    {
        if (game->map.fullmap[(int)(game->player.pos_x + game->player.dir_x * MOVE_SPEED)]
                     [(int)game->player.pos_y] != '1' &&
            game->map.fullmap[(int)(game->player.pos_x + game->player.dir_x * MOVE_SPEED)]
                     [(int)game->player.pos_y] != 'D')
            game->player.pos_x += game->player.dir_x * MOVE_SPEED;
        if (game->map.fullmap[(int)game->player.pos_x]
                     [(int)(game->player.pos_y + game->player.dir_y * MOVE_SPEED)] != '1' &&
            game->map.fullmap[(int)game->player.pos_x]
                     [(int)(game->player.pos_y + game->player.dir_y * MOVE_SPEED)] != 'D')
            game->player.pos_y += game->player.dir_y * MOVE_SPEED;
    }
    if (game->move_backward)
    {
        if (game->map.fullmap[(int)(game->player.pos_x - game->player.dir_x * MOVE_SPEED)]
                     [(int)game->player.pos_y] != '1' &&
            game->map.fullmap[(int)(game->player.pos_x - game->player.dir_x * MOVE_SPEED)]
                     [(int)game->player.pos_y] != 'D')
            game->player.pos_x -= game->player.dir_x * MOVE_SPEED;
        if (game->map.fullmap[(int)game->player.pos_x]
                     [(int)(game->player.pos_y - game->player.dir_y * MOVE_SPEED)] != '1' &&
            game->map.fullmap[(int)game->player.pos_x]
                     [(int)(game->player.pos_y - game->player.dir_y * MOVE_SPEED)] != 'D')
            game->player.pos_y -= game->player.dir_y * MOVE_SPEED;
    }

    // Gestion du mouvement latéral
    if (game->move_left)
    {
        if (game->map.fullmap[(int)game->player.pos_x]
                     [(int)(game->player.pos_y + game->player.dir_x * MOVE_SPEED)] != '1' &&
            game->map.fullmap[(int)game->player.pos_x]
                     [(int)(game->player.pos_y + game->player.dir_x * MOVE_SPEED)] != 'D')
            game->player.pos_y += game->player.dir_x * MOVE_SPEED;
        if (game->map.fullmap[(int)(game->player.pos_x - game->player.dir_y * MOVE_SPEED)]
                     [(int)game->player.pos_y] != '1' &&
            game->map.fullmap[(int)(game->player.pos_x - game->player.dir_y * MOVE_SPEED)]
                     [(int)game->player.pos_y] != 'D')
            game->player.pos_x -= game->player.dir_y * MOVE_SPEED;
    }
    if (game->move_right)
    {
        if (game->map.fullmap[(int)game->player.pos_x]
                     [(int)(game->player.pos_y - game->player.dir_x * MOVE_SPEED)] != '1' &&
            game->map.fullmap[(int)game->player.pos_x]
                     [(int)(game->player.pos_y - game->player.dir_x * MOVE_SPEED)] != 'D')
            game->player.pos_y -= game->player.dir_x * MOVE_SPEED;
        if (game->map.fullmap[(int)(game->player.pos_x + game->player.dir_y * MOVE_SPEED)]
                     [(int)game->player.pos_y] != '1' &&
            game->map.fullmap[(int)(game->player.pos_x + game->player.dir_y * MOVE_SPEED)]
                     [(int)game->player.pos_y] != 'D')
            game->player.pos_x += game->player.dir_y * MOVE_SPEED;
    }
}

int handle_mouse(int x, int y, t_game *game)
{   
    // Calculer la différence de position par rapport au centre
    double rotation_speed = 0.001;
    int delta_x = x - (WINDOW_WIDTH/2);
    
    // Rotation de la caméra
    double old_dir_x = game->player.dir_x;
    game->player.dir_x = game->player.dir_x * cos(-rotation_speed * delta_x) 
        - game->player.dir_y * sin(-rotation_speed * delta_x);
    game->player.dir_y = old_dir_x * sin(-rotation_speed * delta_x) 
        + game->player.dir_y * cos(-rotation_speed * delta_x);
    
    // Rotation du plan de la caméra
    double old_plane_x = game->player.plane_x;
    game->player.plane_x = game->player.plane_x * cos(-rotation_speed * delta_x) 
        - game->player.plane_y * sin(-rotation_speed * delta_x);
    game->player.plane_y = old_plane_x * sin(-rotation_speed * delta_x) 
        + game->player.plane_y * cos(-rotation_speed * delta_x);
    
    return (0);
}