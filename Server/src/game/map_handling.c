
#include "game.h"

int to_supp(float nbr)
{
    if ((nbr - (int) nbr) < 0.0001)
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
    return game->map->tiles[y][x].ressources[index];
}

//function that get the number of ressources in the 8 tiles around the tile yx, avoiding out of bounds
int get_neighbors_repartition(game_t *game, int y, int x, int index)
{
    int res = 0;
    res += game->map->tiles[y][x].ressources[index];
    if (x != 0) {
        res += game->map->tiles[y][x - 1].ressources[index];
        if (y != 0)
            res += game->map->tiles[y - 1][x - 1].ressources[index];
        if (y != (game->map->height - 1))
            res += game->map->tiles[y + 1][x - 1].ressources[index];
    }
    if (y != 0) {
        res += game->map->tiles[y - 1][x].ressources[index];
        if (x != (game->map->width - 1))
            res += game->map->tiles[y - 1][x + 1].ressources[index];
    }
    if (y != (game->map->height - 1)) {
        res += game->map->tiles[y + 1][x].ressources[index];
        if (x != (game->map->width - 1))
            res += game->map->tiles[y + 1][x + 1].ressources[index];
    }
    if (x != (game->map->width - 1))
        res += game->map->tiles[y][x + 1].ressources[index];
    return res;
}

char *get_ressource_name(char *ressource_in, game_t *game, int x, int y)
{
    int ressource = 0, before = 0;
    static const char *mineral_tab[] = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame", "food"};
    for (int i = 0, ressource = 0 ; i < 7 ; i++) {
        while (ressource < game->map->tiles[y][x].ressources[i]) {
            ressource_in = realloc(ressource_in, sizeof(char) * (strlen(ressource_in) + (strlen(mineral_tab[i]) + 2)));
            strcat(ressource_in, " ");
            strcat(ressource_in, mineral_tab[i]);
            ressource++;
        }
    }
    return ressource_in;
}

char *get_ressource_line(game_t *game, )
{

}

char *look(game_t *game, player_t player)
{
    char *ressources = calloc(1, sizeof(char) * 8);
    memcpy(ressources, "[player ", 8);
    int x_mult = (player.entity->orientation.x != 0) ? ((player.entity->orientation.x > 0) ? 1 : -1) : 0;
    int y_mult = (player.entity->orientation.y != 0) ? ((player.entity->orientation.y > 0) ? 1 : -1) : 0;
    int current_view_size = 0, start = 0, end = 0;
    for (int i = 0 ; i < player.entity->level ; i++) {
        current_view_size = 3 + i * 2;
        for (int a = 0 ; a < current_view_size ; a++) {
            
        }
    }
}

game_t *add_in_map(game_t *game, int index, int ressource_to_add)
{
    int randx = 0, randy = 0;
    for (int tolerance = 0 ; ressource_to_add > 0 ; tolerance++) {
        for (int i = 0 ; i < (game->map->height * game->map->width); i++) {
            randx = rand() % game->map->width;
            randy = rand() % game->map->height;
            if (get_neighbors_repartition(game, randx, randy, index) <= tolerance) {
                game->map->tiles[randy][randx].ressources[index] += 1;
                ressource_to_add--;
            }
            if (ressource_to_add == 0) {
                return game;
            }
        }
    }
    return game;
}

game_t *spawn_ressources(game_t *game)
{
    float density[7] = {0.5, 0.3, 0.15, 0.1, 0.1,0.08, 0.05};
    float ressources_available = 0;
    int ressources_to_add = 0;

    for (int i = 0; i < 7 ; i++) {
        ressources_available = get_map_ressources(game, i);
        ressources_to_add = to_supp(game->map->width * game->map->height * density[i + 1] - ressources_available);
        add_in_map(game, i, ressources_to_add);
    }
    return game;
}
