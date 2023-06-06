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

void turn(game_t *game, player_t *player, int direction)
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