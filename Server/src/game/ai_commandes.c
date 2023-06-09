#include "game.h"

static const int for_level[7][8] = {
    // nb player, level_needed, linemate, deraumere, sibur, mendiane, phiras, thystame
    {1, 1, 1, 0, 0, 0, 0, 0},
    {2, 2, 1, 1, 1, 0, 0, 0},
    {2, 3, 2, 0, 1, 0, 2, 0},
    {4, 4, 1, 1, 2, 0, 1, 0},
    {4, 5, 1, 2, 1, 3, 0, 0},
    {6, 6, 1, 2, 3, 0, 1, 0},
    {6, 7, 2, 2, 2, 2, 2, 1}};

static const char *mineral_tab[] = {
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"};

const char *move_forward(game_t *game, player_t *player, const char *arg)
{
    if (player == NULL) {
        return "ko\n";
    }
    if (player->entity->orientation.x == 1)
        player->entity->pos.x = normalize(player->entity->pos.x + 1, game->map->size.x);
    else if (player->entity->orientation.x == -1)
        player->entity->pos.x = normalize(player->entity->pos.x - 1, game->map->size.x);
    else if (player->entity->orientation.y == 1)
        player->entity->pos.y = normalize(player->entity->pos.y + 1, game->map->size.y);
    else if (player->entity->orientation.y == -1)
        player->entity->pos.y = normalize(player->entity->pos.y - 1, game->map->size.y);
    return ("ok\n");
}

const char *turn_left(game_t *game, player_t *player, const char *arg)
{
    if (player == NULL)
        return "ko\n";
    if (player->entity->orientation.x == 0 && player->entity->orientation.y == 1) {
        player->entity->orientation.x = -1;
        player->entity->orientation.y = 0;
    }
    else if (player->entity->orientation.x == -1 && player->entity->orientation.y == 0)
    {
        player->entity->orientation.x = 0;
        player->entity->orientation.y = -1;
    }
    else if (player->entity->orientation.x == 0 && player->entity->orientation.y == -1)
    {
        player->entity->orientation.x = 1;
        player->entity->orientation.y = 0;
    }
    else if (player->entity->orientation.x == 1 && player->entity->orientation.y == 0)
    {
        player->entity->orientation.x = 0;
        player->entity->orientation.y = 1;
    }
    return "ok\n";
}

const char *turn_right(game_t *game ,player_t *player, const char *arg)
{
    if (player == NULL)
        return "ko\n";
    if (player->entity->orientation.x == 0 && player->entity->orientation.y == 1) {
        player->entity->orientation.x = 1;
        player->entity->orientation.y = 0;
    }
    else if (player->entity->orientation.x == 1 && player->entity->orientation.y == 0)
    {
        player->entity->orientation.x = 0;
        player->entity->orientation.y = -1;
    }
    else if (player->entity->orientation.x == 0 && player->entity->orientation.y == -1)
    {
        player->entity->orientation.x = -1;
        player->entity->orientation.y = 0;
    }
    else if (player->entity->orientation.x == -1 && player->entity->orientation.y == 0)
    {
        player->entity->orientation.x = 0;
        player->entity->orientation.y = 1;
    }
    return "ok";
}

const char *team_unused_slots(game_t *game, player_t *player, const char *arg)
{
    team_t *team = get_team(game, arg);
    if (team == NULL)
        return "ko\n";
    memset(game->buffer, 0, BUFSIZ);
    sprintf(game->buffer, "%d\n", team->max_players - team->nb_players);
    return game->buffer;
}

int check_death(game_t *game)
{
    for (list_t ptr = game->players; ptr != NULL; ptr = ptr->next)
    {
        player_t *player = ptr->value;
        if (player->entity->food_left <= 0)
        {
            // send death message
            // TODO: kill player
            return 1;
        }
    }
    return 0;
}

const char *get_inventory(game_t *game, player_t *player, const char *arg)
{
    char *inventory = calloc(1, sizeof(char) * 5);
    char num_buffer[10];
    memset(num_buffer, 0, 10);
    strcat(inventory, "[");
    int before = 0;
    for (int i = 0; i < 6; i++)
    {
        inventory = realloc(inventory, sizeof(char) * (strlen(inventory) + strlen(mineral_tab[i]) + 5));
        if (before == 1)
            strcat(inventory, " ");
        strcat(inventory, mineral_tab[i]);
        strcat(inventory, " ");
        sprintf(num_buffer, "%d", player->entity->minerals[i]);
        printf("%s\n", num_buffer);
        strcat(inventory, num_buffer);
        memset(num_buffer, 0, 10);
        if (i != 5)
            strcat(inventory, ",");
        before = 1;
    }
    strcat(inventory, "]\n");
    return inventory;
}

int get_mineral_index(const char *arg)
{
    for (int i = 0; i < 6; i++) {
        if (strcmp(mineral_tab[i], arg) == 0)
            return i;
    }
    return -1;
}

const char *take_object(game_t *game, player_t *player, const char *arg)
{
    int index = get_mineral_index(arg);
    if (game->map->tiles[player->entity->pos.x][player->entity->pos.y].ressources[index + 1] > 0) {
        game->map->tiles[player->entity->pos.x][player->entity->pos.y].ressources[index + 1]--;
        player->entity->minerals[index]++;
        printf("Player %d take %s\n", player->fd, mineral_tab[index]);
        return "ok\n";
    }
    return "ko\n";
}

const char *drop_object(game_t *game, player_t *player, const char *arg)
{
    int index = get_mineral_index(arg);
    if (player->entity->minerals[index] > 0) {
        game->map->tiles[player->entity->pos.x][player->entity->pos.y].ressources[index + 1]++;
        player->entity->minerals[index]--;
        printf("Player %d dropped %s\n", player->fd, mineral_tab[index]);
        return "ok\n";
    }
    return "ko\n";
}

int check_players(game_t *game, player_t *player, int players_needed, int level_required)
{
    int nb_players = 0;
    for (list_t ptr = game->players; ptr != NULL; ptr = ptr->next)
    {
        player_t *player2 = ptr->value;
        if (player2->entity->pos.x == player->entity->pos.x && player2->entity->pos.y == player->entity->pos.y)
        {
            if (player2->entity->level != level_required)
            {
                nb_players++;
            }
        }
    }
    if (nb_players == players_needed)
    {
        return 0;
    }
    return 1;
}

const char *resolve_incantation(game_t *game, player_t *player, const char *arg)
{
    int lvl = player->entity->level;
    for (int i = 0; i < 6; i++)
    {
        game->map->tiles[player->entity->pos.y][player->entity->pos.x].ressources[i + 1] -= for_level[lvl][i + 2];
    }
    player->entity->level++;
    int leveled_up = 1;
    for (list_t ptr = game->players; ptr != NULL && leveled_up <= for_level[lvl][1]; ptr = ptr->next)
    {
        player_t *player2 = ptr->value;
        if (player2->entity->pos.x == player->entity->pos.x && player2->entity->pos.y == player->entity->pos.y)
        {
            if (player2->entity->level == lvl)
            {
                player2->entity->level++;
                leveled_up++;
            }
        }
    }
    memset(game->buffer, 0, BUFSIZ);
    sprintf(game->buffer, "Current level: %d\n", player->entity->level);
    return game->buffer;
}

const char *verif_incantation(game_t *game, player_t *player, const char *arg)
{
    int lvl = player->entity->level;
    if (check_players(game, player, for_level[lvl][0], for_level[lvl][1]) == 0)
        return "ko\n";
    for (int i = 0; i < 6; i++) {
        if (game->map->tiles[player->entity->pos.y][player->entity->pos.x].ressources[i + 1] < for_level[lvl][i + 2])
            return "ko\n";
    }
    return "Elevation underway\n";
}

char *get_player_in_tile(game_t *game, char *ressources, int x, int y)
{
    for (list_t ptr = game->players; ptr != NULL; ptr = ptr->next) {
        player_t *player = ptr->value;
        if (player->entity->pos.x == x && player->entity->pos.y == y) {
            ressources = realloc(ressources, sizeof(char) * (strlen(ressources) + 8));
            strcat(ressources, "player ");
        }
    }
    return ressources;
}

const char *look(game_t *game, player_t *player, const char *arg)
{
    char *ressources = calloc(1, sizeof(char) * 2);
    memset(ressources, 0, 2);
    memcpy(ressources, "[", 1);
    ressources = get_player_in_tile(game, ressources, player->entity->pos.x, player->entity->pos.y);
    ressources = get_ressource_name(game, ressources, player->entity->pos.x, player->entity->pos.y);
    int x_mult = (player->entity->orientation.x != 0) ? ((player->entity->orientation.x > 0) ? 1 : -1) : 0;
    int y_mult = (player->entity->orientation.y != 0) ? ((player->entity->orientation.y > 0) ? 1 : -1) : 0;
    int current_view_size = 0, start_x = 0, start_y = 0;
    for (int i = 0 ; i < player->entity->level ; i++) {
        current_view_size = 3 + i * 2;
        if (x_mult == 0) {
            start_x = player->entity->pos.x + (y_mult * (i + 1));
            start_y = player->entity->pos.y + (y_mult * (i + 1));
        } else {
            start_x = player->entity->pos.x + (x_mult * (i + 1));
            start_y = player->entity->pos.y - (x_mult * (i + 1));
        }
        for (int a = 0 ; a < current_view_size ; a++) {
            int new_x = start_x - (a * y_mult);
            int new_y = start_y + (a * x_mult);
                ressources = realloc(ressources, sizeof(char) * (strlen(ressources) + 2));
                strcat(ressources, ",");
            if (x_mult == 0) {
                ressources = get_player_in_tile(game, ressources, normalize(new_x, game->map->size.x), normalize(start_y, game->map->size.y));
                ressources = get_ressource_name(game, ressources, normalize(new_x, game->map->size.x), normalize(start_y, game->map->size.y));
            } else {
                ressources = get_player_in_tile(game, ressources, normalize(start_x, game->map->size.x), normalize(new_y, game->map->size.y));
                ressources = get_ressource_name(game, ressources, normalize(start_x, game->map->size.x), normalize(new_y, game->map->size.y));
            }
            ressources = realloc(ressources, sizeof(char) * (strlen(ressources) + 2));
        }
    }
    ressources = realloc(ressources, sizeof(char) * (strlen(ressources) + 3));
    strcat(ressources, "]\n");
    return ressources;
}

void destroy_egg(game_t *game, int x, int y, int *success)
{
    int pos = 0;
    for (list_t ptr = game->eggs ; ptr != NULL ; ptr = ptr->next) {
        egg_t *egg = ptr->value;
        if (egg->pos.x == x && egg->pos.y == y) {
            list_del_elem_at_position(game->eggs, pos);
            *success = 1;
        }
        pos++;
    }
}

const char *eject_player(game_t *game, player_t *player, const char *arg)
{
    int x = player->entity->pos.x;
    int y = player->entity->pos.y;
    int success = 0;
    for (list_t ptr = game->players ; ptr != NULL ; ptr = ptr->next) {
        player_t *player2 = ptr->value;
        if (player2->entity->pos.x == x && player2->entity->pos.y == y && player2 != player) {
            player2->entity->pos.x = normalize(player2->entity->pos.x + 1, game->map->size.x);
            player2->entity->pos.y = normalize(player2->entity->pos.y + 1, game->map->size.y);
            dprintf(player2->fd, "eject: %d\n", get_from_orientation(player));
        }
    }
    destroy_egg(game, player->entity->pos.x, player->entity->pos.y, &success);
    if (success == 1)
        return "ok\n";
    return "ko\n";
}

const char *fork_player(game_t *game, player_t *player, const char *arg)
{

}
