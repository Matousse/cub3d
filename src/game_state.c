#include "../../includes/cub3d.h"

void update_game_state(t_game *game)
{
    if (game->game_state == GAME_STATE_PLAYING)
    {
        game->current_time = time(NULL);
        int elapsed = game->current_time - game->start_time;
        
        // Mise à jour du fog toutes les 1.5 minutes
        game->fog_intensity = (elapsed / FOG_INTERVAL) * 0.2; // Augmente de 20% chaque fois
        if (game->fog_intensity > 0.8) game->fog_intensity = 0.8; // Maximum 80% de fog
        
        // Vérification du temps écoulé
        if (elapsed >= INITIAL_TIME)
        {
            game->game_state = GAME_STATE_GAMEOVER;
        }
    }
}