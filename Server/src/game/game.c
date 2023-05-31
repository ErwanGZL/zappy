
#include "game.h"

minerals_t init_minerals()
{
    minerals_t minerals;
    minerals.deraumere = 0;
    minerals.sibur = 0;
    minerals.mendiane = 0;
    minerals.phiras = 0;
    minerals.thystame = 0;
    minerals.linemate = 0;
    return minerals;
}

map_t *init_map(int width, int height)
{
    map_t *map = calloc(1, sizeof(map_t));
    map->width = width;
    map->height = height;
    map->tiles = calloc(width, sizeof(map_tile_t *));
    for (int i = 0; i < width; i++) {
        map->tiles[i] = calloc(height, sizeof(map_tile_t));
        map->tiles[i]->food = 0;
        map->tiles[i]->minerals = init_minerals();
        map->tiles[i]->player_id = -1;
    }
    return map;
}

game_t *init_game(int width, int height)
{
    game_t *game = calloc(1, sizeof(game_t));
    game->nb_players = 0;
    game->nb_teams = 0;
    game->map = init_map(width, height);
    game->players = NULL;
    game->teams = NULL;
    return game;
}
