
#include "game.h"

int game()
{
    team_t *team = calloc(1, sizeof(team_t));
    team->name = "test1";
    list_t test = malloc(sizeof(node_t));
    test->value = team;
    test->next = NULL;
    team_t *team2 = calloc(1, sizeof(team_t));
    team2->name = "test2";
    list_add_elem_at_back(&test, team2);
    for (list_t ptr = test ; ptr != NULL; ptr = ptr->next)
        printf("%s\n", ((team_t *)ptr->value)->name);
    return 0;
}
