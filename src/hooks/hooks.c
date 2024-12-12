//hooks.c

#include "../../includes/cub3d.h"

/* Gestion des touches */
int key_press(int keycode, t_game *game)
{
    double old_dir_x;
    double old_plane_x;

    if (keycode == 65307) /* ESC */
        exit(0);
    else if (keycode == 122) /* Z - Avancer */
    {
        if (game->map[(int)(game->player.pos_x + game->player.dir_x * MOVE_SPEED)]
                     [(int)game->player.pos_y] != '1')
            game->player.pos_x += game->player.dir_x * MOVE_SPEED;
        if (game->map[(int)game->player.pos_x]
                     [(int)(game->player.pos_y + game->player.dir_y * MOVE_SPEED)] != '1')
            game->player.pos_y += game->player.dir_y * MOVE_SPEED;
    }
    else if (keycode == 115) /* S - Reculer */
    {
        if (game->map[(int)(game->player.pos_x - game->player.dir_x * MOVE_SPEED)]
                     [(int)game->player.pos_y] != '1')
            game->player.pos_x -= game->player.dir_x * MOVE_SPEED;
        if (game->map[(int)game->player.pos_x]
                     [(int)(game->player.pos_y - game->player.dir_y * MOVE_SPEED)] != '1')
            game->player.pos_y -= game->player.dir_y * MOVE_SPEED;
    }
    else if (keycode == 65363) /* Flèche gauche */
    {
        old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(ROTATION_SPEED) 
                          - game->player.dir_y * sin(ROTATION_SPEED);
        game->player.dir_y = old_dir_x * sin(ROTATION_SPEED) 
                          + game->player.dir_y * cos(ROTATION_SPEED);
        old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(ROTATION_SPEED) 
                            - game->player.plane_y * sin(ROTATION_SPEED);
        game->player.plane_y = old_plane_x * sin(ROTATION_SPEED) 
                            + game->player.plane_y * cos(ROTATION_SPEED);
    }
    else if (keycode == 65361) /* Flèche droite */
    {
        old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(-ROTATION_SPEED) 
                          - game->player.dir_y * sin(-ROTATION_SPEED);
        game->player.dir_y = old_dir_x * sin(-ROTATION_SPEED) 
                          + game->player.dir_y * cos(-ROTATION_SPEED);
        old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(-ROTATION_SPEED) 
                            - game->player.plane_y * sin(-ROTATION_SPEED);
        game->player.plane_y = old_plane_x * sin(-ROTATION_SPEED) 
                            + game->player.plane_y * cos(-ROTATION_SPEED);
    }
    return (0);
}