#include "../../includes/cub3d.h"

void update_game_state(t_game *game)
{
    if (game->game_state == GAME_STATE_PLAYING)
    {
        game->current_time = time(NULL);
        int elapsed = game->current_time - game->start_time;
            
        // Vérification du temps écoulé
        if (elapsed >= INITIAL_TIME)
            game->game_state = GAME_STATE_GAMEOVER;
    }
}