
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

int get_tile_ressource(game_t *game, int x, int y)
{
    int res = 0;
    for (int i = 0; i < 7; i++) {
        res += game->map->tiles[y][x].ressources[i];
    }
    return res;
}

void print_ressources(game_t *game)
{
    for (int y = 0 ; y < game->map->height ; y++) {
        for (int x = 0 ; x < game->map->width ; x++) {
            printf("x: %d, y: %d = ", x, y);
            for (int i = 0 ; i < 7 ; i++) {
                printf("%d, ", game->map->tiles[y][x].ressources[i]);
            }
            printf("\n");
        }
    }
}

char *get_ressource_name(game_t *game, char *ressource_in, int x, int y)
{
    int before = 0;
    static const char *mineral_tab[] = {"food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
    for (int i = 0, ressource = 0 ; i < 7 ; i++) {
        while (ressource < game->map->tiles[y][x].ressources[i]) {
            ressource_in = realloc(ressource_in, sizeof(char) * (strlen(ressource_in) + (strlen(mineral_tab[i]) + 2)));
            if (before != 0)
                strcat(ressource_in, " ");
            strcat(ressource_in, mineral_tab[i]);
            ressource++;
            before = 1;
        }
    }
    return ressource_in;
}

char *look(game_t *game, player_t player)
{
    char *ressources = calloc(1, sizeof(char) * 9);
    memcpy(ressources, "[player ", 8);
    ressources = get_ressource_name(game, ressources, player.entity->pos.x, player.entity->pos.y);
    int x_mult = (player.entity->orientation.x != 0) ? ((player.entity->orientation.x > 0) ? 1 : -1) : 0;
    int y_mult = (player.entity->orientation.y != 0) ? ((player.entity->orientation.y > 0) ? 1 : -1) : 0;
    int current_view_size = 0, start_x = 0, start_y = 0;
    for (int i = 0 ; i < player.entity->level ; i++) {
        current_view_size = 3 + i * 2;
        if (x_mult == 0) {
            start_x = player.entity->pos.x + (y_mult * (i + 1));
            start_y = player.entity->pos.y + (y_mult * (i + 1));
        } else {
            start_x = player.entity->pos.x + (x_mult * (i + 1));
            start_y = player.entity->pos.y - (x_mult * (i + 1));
        }
        for (int a = 0 ; a < current_view_size ; a++) {
            int new_x = start_x - (a * y_mult);
            int new_y = start_y + (a * x_mult);
                ressources = realloc(ressources, sizeof(char) * (strlen(ressources) + 2));
                strcat(ressources, ",");
            if (x_mult == 0) {
                ressources = get_ressource_name(game, ressources, NORMALIZE(new_x, game->map->width), NORMALIZE(start_y, game->map->height));
            } else {
                ressources = get_ressource_name(game, ressources, NORMALIZE(start_x, game->map->width), NORMALIZE(new_y, game->map->height));
            }
            ressources = realloc(ressources, sizeof(char) * (strlen(ressources) + 2));
        }
    }
    strcat(ressources, "]");
    return ressources;
}

game_t *add_in_map(game_t *game, int index, int ressource_to_add)
{
    int randx = 0, randy = 0;
    for (int tolerance = 0 ; ressource_to_add > 0 ; tolerance++) {
        for (int i = 0 ; i < (game->map->height * game->map->width) ; i++) {
            randx = rand() % game->map->width;
            randy = rand() % game->map->height;
            // if (get_neighbors_repartition(game, randx, randy, index) <= tolerance) {
            if (get_tile_ressource(game, randx, randy) <= tolerance) {
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
        ressources_to_add = to_supp(game->map->width * game->map->height * density[i] - ressources_available);
        add_in_map(game, i, ressources_to_add);
    }
    return game;
}
