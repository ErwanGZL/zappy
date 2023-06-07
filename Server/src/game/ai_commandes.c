#include "game.h"

void move_up(game_t *game, player_t *player)
{
    if (player != NULL)
        player->entity->pos.y = normalize(player->entity->pos.y - 1, game->map->size.y);
}

void turn_left(player_t *player)
{
    if (player == NULL)
        return;
    if (player->entity->orientation.x == 0 && player->entity->orientation.y == 1) {
        player->entity->orientation.x = -1;
        player->entity->orientation.y = 0;
    } else if (player->entity->orientation.x == -1 && player->entity->orientation.y == 0) {
        player->entity->orientation.x = 0;
        player->entity->orientation.y = -1;
    } else if (player->entity->orientation.x == 0 && player->entity->orientation.y == -1) {
        player->entity->orientation.x = 1;
        player->entity->orientation.y = 0;
    } else if (player->entity->orientation.x == 1 && player->entity->orientation.y == 0) {
        player->entity->orientation.x = 0;
        player->entity->orientation.y = 1;
    }
}

void turn_right(player_t *player)
{
    if (player == NULL)
        return;
    if (player->entity->orientation.x == 0 && player->entity->orientation.y == 1) {
        player->entity->orientation.x = 1;
        player->entity->orientation.y = 0;
    } else if (player->entity->orientation.x == 1 && player->entity->orientation.y == 0) {
        player->entity->orientation.x = 0;
        player->entity->orientation.y = -1;
    } else if (player->entity->orientation.x == 0 && player->entity->orientation.y == -1) {
        player->entity->orientation.x = -1;
        player->entity->orientation.y = 0;
    } else if (player->entity->orientation.x == -1 && player->entity->orientation.y == 0) {
        player->entity->orientation.x = 0;
        player->entity->orientation.y = 1;
    }
}

void turn(player_t *player, int direction)
{
    if (player == NULL)
        return;
    if (direction == 1) {
        turn_left(player);
    } else if (direction == 2) {
        turn_right(player);
    }
}

int team_unused_slots(team_t *team)
{
    if (team == NULL)
        return -1;
    return team->max_players - team->nb_players;
}

int check_death(game_t *game)
{
   for (list_t ptr = game->players; ptr != NULL; ptr = ptr->next) {
        player_t *player = ptr->value;
        if (player->entity->food_left <= 0) {
            //send death message
            //TODO: kill player
            return 1;
        }
    }
    return 0;
}

char *get_inventory(player_t *player)
{
    static const char *mineral_tab[] = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
    char *inventory = calloc(1, sizeof(char) * 5);
    char num_buffer[10];
    memset(num_buffer, 0, 10);
    strcat(inventory, "[");
    int before = 0;
    for (int i = 0; i < 6; i++) {
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

int take_object(game_t *game, player_t *player, int index)
{
    static const char *mineral_tab[] = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
    if (game->map->tiles[player->entity->pos.x][player->entity->pos.y].ressources[index + 1] > 0) {
        game->map->tiles[player->entity->pos.x][player->entity->pos.y].ressources[index + 1]--;
        player->entity->minerals[index]++;
        printf("Player %d take %s\n", player->fd, mineral_tab[index]);
        //send ok
        return 0;
    }
    //send ko
    return 1;
}

int drop_object(game_t *game, player_t *player, int index)
{
    static const char *mineral_tab[] = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
    if (player->entity->minerals[index] > 0) {
        game->map->tiles[player->entity->pos.x][player->entity->pos.y].ressources[index + 1]++;
        player->entity->minerals[index]--;
        printf("Player %d dropped %s\n", player->fd, mineral_tab[index]);
        //send ok
        return 0;
    }
    //send ko
    return 1;
}

int check_players(game_t *game, player_t *player, int players_needed, int level_required)
{
    int nb_players = 0;
    for (list_t ptr = game->players; ptr != NULL; ptr = ptr->next) {
        player_t *player2 = ptr->value;
        if (player2->entity->pos.x == player->entity->pos.x && player2->entity->pos.y == player->entity->pos.y) {
            if (player2->entity->level != level_required) {
                nb_players++;
            }
        }
    }
    if (nb_players == players_needed) {
        return 0;
    }
    return 1;
}

void resolve_incantation(game_t *game, player_t *player, int nbr_to_lvl_up, int lvl)
{
    player->entity->level++;
    int leveled_up = 1;
    for (list_t ptr = game->players; ptr != NULL && leveled_up <= nbr_to_lvl_up ; ptr = ptr->next) {
        player_t *player2 = ptr->value;
        if (player2->entity->pos.x == player->entity->pos.x && player2->entity->pos.y == player->entity->pos.y) {
            if (player2->entity->level == lvl) {
                player2->entity->level++;
                leveled_up++;
            }
        }
    }
}

int incantate(game_t *game, player_t *player)
{
    int lvl = player->entity->level;
    static const int for_level[7][8] = {
    //nb player, level_needed, linemate, deraumere, sibur, mendiane, phiras, thystame
        { 1, 1, 1, 0, 0, 0, 0, 0 },
        { 2, 2, 1, 1, 1, 0, 0, 0 },
        { 2, 3, 2, 0, 1, 0, 2, 0 },
        { 4, 4, 1, 1, 2, 0, 1, 0 },
        { 4, 5, 1, 2, 1, 3, 0, 0 },
        { 6, 6, 1, 2, 3, 0, 1, 0 },
        { 6, 7, 2, 2, 2, 2, 2, 1 }
    };
    if (check_players(game, player, for_level[lvl][0], for_level[lvl][1]) == 0)
        return 1;
    for (int i = 0; i < 6; i++) {
        if (game->map->tiles[player->entity->pos.y][player->entity->pos.x].ressources[i + 1] < for_level[lvl][i + 2])
            return 1;
    }
    for (int i = 0; i < 6; i++) {
        game->map->tiles[player->entity->pos.y][player->entity->pos.x].ressources[i + 1] -= for_level[lvl][i + 2];
    }
    resolve_incantation(game, player, for_level[lvl][0], lvl);
    return 0;
}
