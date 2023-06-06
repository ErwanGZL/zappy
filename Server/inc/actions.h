
#pragma once

#include "list.h"
#include <time.h>

typedef struct action_s {
    enum actions_e {
        ACTION_NONE,
        ACTION_FORWARD,
        ACTION_LEFT,
        ACTION_RIGHT,
        ACTION_LOOK,
        ACTION_INVENTORY,
        ACTION_BROADCAST,
        ACTION_CONNECT_NBR,
        ACTION_FORK,
        ACTION_EJECT,
        ACTION_TAKE,
        ACTION_SET,
        ACTION_INCANTATION,
    } type;
    int issuer;
    time_t time;
} action_t;

action_t *action_new(int issuer, const char *cmd);
bool accept_action(list_t action_list, action_t *action);
bool action_exec(action_t *action);
int action_cmp(const void *a, const void *b);
