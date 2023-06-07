#include "game.h"

char *gui_map_size(game_t *game)
{
    char *str = calloc(1, sizeof(char) * 11);
    memset(str, 0, 11);
    sprintf(str, "msz %d %d\n", game->map->size.x, game->map->size.y);
    return str;
}

char *gui_tile_content(game_t *game, int x, int y)
{
    char *str = calloc(1, sizeof(char) * 50);
    memset(str, 0, 50);
    sprintf(str, "bct %d %d %d %d %d %d %d %d %d\n", x, y, ress[0], ress[1], ress[2], ress[3], ress[4], ress[5], ress[6]);
    return str;
}

char *gui_map_content(game_t *game)
{
    char *str = calloc(1, sizeof(char) * BUFSIZ);
    char buffer[BUFSIZ] = {0};
    memset(str, 0, 100);
    for (int y = 0; y < game->map->size.y; y++) {
        for (int x = 0; x < game->map->size.x; x++) {
            memcpy(buffer, str, strlen(str));
            sprintf(str, "%sbct %d %d %d %d %d %d %d %d %d\n", buffer, x, y, ress[0], ress[1], ress[2], ress[3], ress[4], ress[5], ress[6]);
        }
    }
    return str;
}

char *gui_team_names(game_t *game)
{
    char *str = calloc(1, sizeof(char) * BUFSIZ);
    char buffer[BUFSIZ] = {0};
    memset(str, 0, 100);
    for (list_t ptr = game->teams ; ptr != NULL ; ptr = ptr->next) {
        memcpy(buffer, str, strlen(str));
        sprintf(str, "%stna %s\n", buffer, ((team_t *) ptr->value)->name);
    }
    return str;
}
