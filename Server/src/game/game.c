
#include "game.h"

team_t **get_team(game_t *game, team_name_t team_name)
{
    for (list_t ptr = game->teams; ptr != NULL; ptr = ptr->next)
        if ( strcmp(((team_t *) ptr->value)->name, team_name) == 0)
            return ((team_t **) &ptr->value);
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
    player->team_name = team_name;
    player->entity = calloc(1, sizeof(entity_t));
    player->entity->pos.x = rand() % game->map->width;
    player->entity->pos.y = rand() % game->map->height;
    player->entity->level = 1;
    player->entity->orientation = (pos_t) {1,1};
    player->entity->food_left = 1260;
    player->entity->minerals = init_minerals();
    list_add_elem_at_back(&game->players, player);
    team_t **ptr = get_team(game, team_name);
    if (ptr != NULL)
        (*ptr)->nb_players++;
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

map_t *init_map(int width, int height)
{
    map_t *map = calloc(1, sizeof(map_t));
    map->width = width;
    map->height = height;
    map->tiles = calloc(height, sizeof(map_tile_t *));
    for (int i = 0; i < height; i++) {
        map->tiles[i] = calloc(width, sizeof(map_tile_t));
        for (int a = 0 ; a < width ; a++) {
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
    game->nb_players = 0;
    game->nb_teams = 0;
    game->map = init_map(opt->width, opt->height);
    game->players = NULL;
    for (list_t head = opt->teams; head != NULL; head = head->next)
    {
        team_name_t name = (team_name_t) head->value;
        add_team(game, opt->clientsNb, name);
    }
    return game;
}
