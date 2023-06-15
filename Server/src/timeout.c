#include "typedef.h"
#include "server.h"
#include "actions.h"
#include "list.h"
#include "game.h"

timeval_t *player_get_next_food_timeout(list_t players, int freq)
{
    if (players == NULL)
        return NULL;
    timeval_t *timeout = calloc(1, sizeof(timeval_t));
    int food_timer_units = ((player_t *)players->value)->entity->food_timer_units;
    for (list_t head = players->next; head != NULL; head = head->next)
    {
        player_t *player = (player_t *)head->value;
        if (strncmp(player->team_name, "GRAPHIC", 7) == 0)
            continue;
        food_timer_units = player->entity->food_timer_units < food_timer_units
                               ? player->entity->food_timer_units
                               : food_timer_units;
    }
    timeout->tv_usec = ((double)food_timer_units / freq) * 1000000;
    return timeout;
}

timeval_t *actions_get_next_timeout(list_t action_list, int frequency)
{
    if (action_list == NULL)
        return NULL;
    timeval_t *timeout = calloc(1, sizeof(timeval_t));
    list_sort(&action_list, action_cmp_cooldown);
    action_t *action = (action_t *)action_list->value;
    timeout->tv_usec = ((double)action->cooldown / frequency) * 1000000;
    return timeout;
}

timeval_t *server_get_next_timeout(server_t *server)
{
    timeval_t *action_timeout = actions_get_next_timeout(server->actions, server->game->freq);
    timeval_t *pfood_timeout = player_get_next_food_timeout(server->game->players, server->game->freq);
    if (action_timeout == NULL && pfood_timeout == NULL)
        return NULL;
    else if (action_timeout == NULL)
        return pfood_timeout;
    else if (pfood_timeout == NULL)
        return action_timeout;

    timeval_t *next = calloc(1, sizeof(timeval_t));
    printf("Action timeout : %ld.%ld\n", action_timeout->tv_sec, action_timeout->tv_usec);
    printf("Player food timeout : %ld.%ld\n", pfood_timeout->tv_sec, pfood_timeout->tv_usec);
    memcpy(
        next,
        MIN_TIMEVAL(action_timeout, pfood_timeout),
        sizeof(timeval_t));
    free(action_timeout);
    free(pfood_timeout);
    if (next->tv_sec == 0 && next->tv_usec == 0)
    {
        printf("No timeout\n");
        free(next);
        return NULL;
    }
    printf("Next timeout : %ld.%ld\n", next->tv_sec, next->tv_usec);
    return next;
}
