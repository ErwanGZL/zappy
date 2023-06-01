
#include "game.h"

int to_supp(float nbr)
{
    if (nbr - (int) nbr < 0.0001)
        return nbr;
    return (int) ceilf(nbr);
}

int get_map_ressources(game_t *game,int index)
{
    int res = 0;
    for (int i = 0; i < game->map->height ; i++) {
        for (int a = 0; a < game->map->width ; a++) {
            res += get_ressource(game, i, a, index);
        }
    }
    return res;
}

int get_ressource(game_t *game, int x, int y, int index)
{
    return game->map->tiles[y][x].minerals[index];
}

int get_neighbors_repartition(game_t *game, int y, int x, int index)
{
    int res = 0;
    res += game->map->tiles[y][x].minerals[index];
    if (x != 0) {
        res += game->map->tiles[y][x - 1].minerals[index];
        if (y != 0)
            res += game->map->tiles[y - 1][x - 1].minerals[index];
        if (y != (game->map->height - 1))
            res += game->map->tiles[y + 1][x - 1].minerals[index];
    }
    if (y != 0) {
        res += game->map->tiles[y - 1][x].minerals[index];
        if (x != (game->map->width - 1))
            res += game->map->tiles[y - 1][x + 1].minerals[index];
    }
    if (y != (game->map->height - 1)) {
        res += game->map->tiles[y + 1][x].minerals[index];
        if (x != (game->map->width - 1))
            res += game->map->tiles[y + 1][x + 1].minerals[index];
    }
    if (x != (game->map->width - 1))
        res += game->map->tiles[y][x + 1].minerals[index];
    return res;
}

game_t *add_in_map(game_t *game, int index, int ressource_to_add)
{
    for (int tolerance = 0 ; ressource_to_add > 0 ; tolerance++) {
        for (int i = 0 ; i < game->map->height ; i++) {
            for (int a = 0 ; a < game->map->width ; a++) {
                if (get_neighbors_repartition(game, i, a, index) <= tolerance) {
                    game->map->tiles[i][a].minerals[index] += 1;
                    ressource_to_add--;
                }
                if (ressource_to_add == 0) {
                    return game;
                }
            }
        }
    }
    return game;
}

game_t *spawn_ressources(game_t *game)
{
    float density[7] = {0.5, 0.3, 0.15, 0.1, 0.05, 0.01, 0.0};
    float ressources_available = 0;
    int ressources_to_add = 0;
    for (int i = 0; i < 6 ; i++) {
        ressources_available = get_map_ressources(game, i);
        ressources_to_add = to_supp(game->map->width * game->map->height * density[i + 1] - ressources_available);
        add_in_map(game, i, ressources_to_add);
    }
    return game;
}
