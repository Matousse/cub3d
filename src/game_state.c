#include "../../includes/cub3d.h"

void update_game_state(t_game *game)
{
    if (game->game_state == GAME_STATE_PLAYING)
    {
        game->current_time = time(NULL);
        int elapsed = game->current_time - game->start_time;
        
        // Mise à jour du fog toutes les 1.5 minutes
        game->fog_level = elapsed / FOG_INTERVAL;
        if (game->fog_level > MAX_FOG_LEVELS)
            game->fog_level = MAX_FOG_LEVELS;
            
        // Réduire la distance de vue en fonction du niveau de brouillard
        game->view_distance = BASE_VIEW_DISTANCE / (game->fog_level + 1);
        
        // Vérification du temps écoulé
        if (elapsed >= INITIAL_TIME)
            game->game_state = GAME_STATE_GAMEOVER;
    }
}