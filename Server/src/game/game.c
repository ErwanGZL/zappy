
#include "game.h"
#include <string.h>

team_t *get_team_by_name(game_t *game, const char *team_name)
{
    for (list_t ptr = game->teams; ptr != NULL; ptr = ptr->next)
        if (strcmp(((team_t *)ptr->value)->name, team_name) == 0)
            return ((team_t *)ptr->value);
    return NULL;
}


int *init_ressources()
{
    int *res = calloc(7, sizeof(int));
    for (int i = 0; i < 7; i++)
        res[i] = 0;
    return res;
}

int *init_minerals()
{
    int *res = calloc(6, sizeof(int));
    for (int i = 0; i < 6; i++)
        res[i] = 0;
    return res;
}

game_t *add_player(game_t *game, team_name_t team_name, int fd)
{
    player_t *player = calloc(1, sizeof(player_t));
    player->fd = fd;
    player->team_name = strdup(team_name);
    player->entity = calloc(1, sizeof(entity_t));
    player->entity->pos.x = rand() % game->map->size.x;
    player->entity->pos.y = rand() % game->map->size.y;
    player->entity->level = 1;
    player->entity->orientation = (pos_t){1, 0};
    player->entity->food_left = 10;
    player->entity->minerals = init_minerals();
    list_add_elem_at_back(&game->players, player);
    team_t *ptr = get_team_by_name(game, team_name);
    if (ptr != NULL)
        ptr->nb_players++;
    game->nb_players++;
    return game;
}

game_t *add_team(game_t *game, int max_players, team_name_t name)
{
    team_t *team = calloc(1, sizeof(team_t));
    team->max_players = max_players;
    team->name = name;
    list_add_elem_at_back(&game->teams, team);
    game->nb_teams++;
    return game;
}

game_t *add_egg(game_t *game, team_name_t team_name)
{
    egg_t *egg = calloc(1, sizeof(egg_t));
    egg->team_name = strdup(team_name);
    egg->pos.x = rand() % game->map->size.x;
    egg->pos.y = rand() % game->map->size.y;
    egg->id = game->egg_nbr;
    list_add_elem_at_back(&game->eggs, egg);
    game->egg_nbr++;
    return game;
}

map_t *init_map(int width, int height)
{
    map_t *map = calloc(1, sizeof(map_t));
    map->size.x = width;
    map->size.y = height;
    map->tiles = calloc(height, sizeof(map_tile_t *));
    for (int i = 0; i < height; i++)
    {
        map->tiles[i] = calloc(width, sizeof(map_tile_t));
        for (int a = 0; a < width; a++)
        {
            map->tiles[i][a].ressources = init_ressources();
            map->tiles[i][a].player_id = -1;
        }
    }
    return map;
}

game_t *init_game(option_t *opt)
{
    srand(time(NULL));
    game_t *game = calloc(1, sizeof(game_t));
    game->freq = opt->freq;
    game->nb_players = 0;
    game->nb_teams = 0;
    game->map = init_map(opt->width, opt->height);
    game->players = NULL;
    game->eggs = NULL;
    for (list_t head = opt->teams; head != NULL; head = head->next)
    {
        team_name_t name = (team_name_t)head->value;
        add_team(game, opt->clientsNb, name);
    }
    memset(game->send_message, 0, BUFSIZ);
    memset(game->buffer, 0, BUFSIZ / 2);
    return game;
}

game_t *remove_player(game_t *game, int fd)
{
    int i = 0;
    for (list_t ptr = game->players; ptr != NULL; ptr = ptr->next, i++) {
        if (((player_t *) ptr->value)->fd == fd) {
            team_t *ptr2 = get_team_by_name(game, ((player_t *) ptr->value)->team_name);
            if (ptr2 != NULL)
                ptr2->nb_players--;
            game->nb_players--;
            list_del_elem_at_position(&game->players, i);
            break;
        }
    }
    return game;
}

void free_game(game_t *game)
{
    for (list_t ptr = game->players; ptr != NULL; ptr = ptr->next) {
        free(((player_t *) ptr->value)->entity->minerals);
        free(((player_t *) ptr->value)->entity);
        free(ptr->value);
    }
    for (list_t ptr = game->teams; ptr != NULL; ptr = ptr->next)
        free(ptr->value);
    for (int i = 0; i < game->map->size.y; i++) {
        for (int a = 0; a < game->map->size.x; a++)
            free(game->map->tiles[i][a].ressources);
        free(game->map->tiles[i]);
    }
    free(game->map->tiles);
    free(game->map);
    free(game);
}

player_t *get_player_by_fd(game_t *game, int fd)
{
    for (list_t ptr = game->players; ptr != NULL; ptr = ptr->next) {
        if (((player_t *) ptr->value)->fd == fd)
            return ((player_t *) ptr->value);
    }
    return NULL;
}

int get_orientation(player_t * player)
{
    pos_t orientation = player->entity->orientation;
    if (orientation.y == -1)
        return 1;
    if (orientation.x == 1)
        return 2;
    if (orientation.y == 1)
        return 3;
    if (orientation.x == -1)
        return 4;
    return 0;
}

int get_from_orientation(player_t * player)
{
    pos_t orientation = player->entity->orientation;
    if (orientation.y == -1)
        return 3;
    if (orientation.x == 1)
        return 4;
    if (orientation.y == 1)
        return 1;
    if (orientation.x == -1)
        return 2;
    return 0;
}

void destroy_egg(game_t *game, int x, int y, int *success)
{
    int pos = 0;
    for (list_t ptr = game->eggs ; ptr != NULL ; ptr = ptr->next) {
        egg_t *egg = ptr->value;
        if (egg->pos.x == x && egg->pos.y == y) {
            list_del_elem_at_position(&game->eggs, pos);
            *success = 1;
        }
        //remove a place in the team
        pos++;
    }
}
