#include "actions.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static const char *actions[] = {
    "Forward",
    "Right",
    "Left",
    "Look",
    "Inventory",
    "Broadcast ",
    "Connect_nbr",
    "Fork",
    "Eject",
    "Take ",
    "Set ",
    "Incantation",
    NULL};

static const int cooldowns[] = {
    7,
    7,
    7,
    7,
    1,
    7,
    0,
    42,
    7,
    7,
    7,
    300};

/**
 * TODO: Callback needs to return a structure containing the response
*/
static const char *(*callbacks[])(game_t *, player_t *, const char *) = {
    &move_forward,
    &turn_right,
    &turn_left,
    &look,
    &get_inventory,
    &broadcast,
    &team_unused_slots,
    &fork_player,
    &eject_player,
    &take_object,
    &drop_object,
    &resolve_incantation};

action_t *action_new(int issuer, const char *cmd)
{
    action_t *action = calloc(1, sizeof(action_t));
    action->issuer = issuer;
    for (int i = 0; actions[i] != NULL; i++)
    {
        if (strncmp(cmd, actions[i], strlen(actions[i])) == 0)
        {
            action->type = i + 1;
            action->cooldown = cooldowns[action->type];
            action->callback = callbacks[action->type];
            if (action->type == ACTION_BROADCAST || action->type == ACTION_TAKE || action->type == ACTION_SET)
                strncpy(action->arg, cmd + strlen(actions[i]), strlen(cmd) - strlen(actions[i]) - 1);
            printf("Action arg: %s\n", action->arg);
        }
    }
    if (action->type == 0)
    {
        printf("Unknown command: %s\n", cmd);
        free(action);
        return NULL;
    }
    printf("New action: %s\n", cmd);
    printf("Action type: %d\n", action->type);
    printf("Action cooldown: %d\n", action->cooldown);
    return action;
}

int action_cmp_cooldown(const void *a, const void *b)
{
    action_t *action_a = (action_t *)a;
    action_t *action_b = (action_t *)b;
    if (action_a->cooldown < action_b->cooldown)
        return -1;
    if (action_a->cooldown > action_b->cooldown)
        return 1;
    return 0;
}

bool actions_accept(list_t *action_list, action_t *action)
{
    if (action == NULL)
        return false;
    int occ = 0;
    for (list_t head = *action_list; head != NULL; head = head->next)
    {
        action_t *a = (action_t *)head->value;
        if (a->issuer == action->issuer)
            occ++;
    }
    if (occ < 10)
    {
        printf("Action accepted\n");
        list_add_elem_at_back(action_list, action);
        return true;
    }
    printf("Too many actions for client %d\n", action->issuer);
    free(action);
    return false;
}

timeval_t *actions_get_next_timeout(list_t action_list, int frequency)
{
    if (action_list == NULL)
        return NULL;
    timeval_t *timeout = calloc(1, sizeof(timeval_t));
    list_sort(&action_list, action_cmp_cooldown);
    action_t *action = (action_t *)action_list->value;
    timeout->tv_usec = (action->cooldown / frequency) * 1000000;
    return timeout;
}

void actions_apply_elapsed_time(list_t action_list, size_t elapsed_time)
{
    for (list_t head = action_list; head != NULL; head = head->next)
    {
        action_t *action = (action_t *)head->value;
        action->cooldown -= elapsed_time;
    }
}
