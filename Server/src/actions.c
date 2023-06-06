#include "actions.h"

static const char *actions[] = {
    "Forward",
    "Right",
    "Left",
    "Look",
    "Inventory",
    "Broadcast",
    "Connect_nbr",
    "Fork",
    "Eject",
    "Take",
    "Set",
    "Incantation",
    NULL};

static const int time[] = {
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
    300,
};

action_t *action_new(int issuer, const char *cmd)
{
    action_t *action = calloc(1, sizeof(action_t));
    action->issuer = issuer;
    for (int i = 0; actions[i] != NULL; i++)
    {
        if (strncmp(cmd, actions[i], strlen(actions[i])) == 0)
        {
            action->type = i + 1;
            action->time = time[action->type];
        }
    }
    if (action->type == 0)
    {
        free(action);
        return NULL;
    }
    return action;
}

bool accept_action(list_t action_list, action_t *action)
{
    int occ = 0;
    for (list_t head = action_list; head != NULL; head = head->next)
    {
        action_t *a = (action_t *)head->value;
        if (a->issuer == action->issuer)
            occ++;
    }
    if (occ < 10)
    {
        list_add_elem_at_back(&action_list, action);
        return true;
    }
    free(action);
    return false;
}

int action_cmp(const void *a, const void *b)
{
    action_t *action_a = (action_t *)a;
    action_t *action_b = (action_t *)b;
    if (action_a->time < action_b->time)
        return -1;
    if (action_a->time > action_b->time)
        return 1;
    return 0;
}
