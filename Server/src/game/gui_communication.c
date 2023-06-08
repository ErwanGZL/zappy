#include "game.h"

char *gui_map_size(game_t *game)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "msz %d %d\n", game->map->size.x, game->map->size.y);
    return game->send_message;
}

char *gui_tile_content(game_t *game, int x, int y)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "bct %d %d %d %d %d %d %d %d %d\n", x, y, ress[0], ress[1], ress[2], ress[3], ress[4], ress[5], ress[6]);
    return game->send_message;
}

char *gui_map_content(game_t *game)
{
    memset(game->buffer, 0, BUFSIZ / 2);
    memset(game->send_message, 0, BUFSIZ);
    for (int y = 0; y < game->map->size.y; y++) {
        for (int x = 0; x < game->map->size.x; x++) {
            memcpy(game->buffer, game->send_message, strlen(game->send_message));
            sprintf(game->send_message, "%sbct %d %d %d %d %d %d %d %d %d\n", game->buffer, x, y, ress[0], ress[1], ress[2], ress[3], ress[4], ress[5], ress[6]);
            memset(game->buffer, 0, BUFSIZ / 2);
        }
    }
    return game->send_message;
}

char *gui_team_names(game_t *game)
{
    memset(game->send_message, 0, BUFSIZ);
    memset(game->buffer, 0, BUFSIZ / 2);
    for (list_t ptr = game->teams ; ptr != NULL ; ptr = ptr->next) {
        memcpy(game->buffer, game->send_message, strlen(game->send_message));
        sprintf(game->send_message, "%stna %s\n", game->buffer, ((team_t *) ptr->value)->name);
    }
    return game->send_message;
}
