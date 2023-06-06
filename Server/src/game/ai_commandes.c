#include "game.h"

void move_up(game_t *game, int fd)
{
    for (list_t ptr = game->players; ptr != NULL; ptr = ptr->next) {
        if (((player_t *) ptr->value)->fd == fd) {
            ((player_t *) ptr->value)->entity->pos.y--;
            GET_POS(((player_t *) ptr->value)->entity->pos, game->map->size);
        }
    }
}