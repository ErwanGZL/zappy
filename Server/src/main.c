/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** main
*/

#include "server.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

int main(int argc, char *argv[])
{
    game_t *game = init_game(10, 10);
    //game = spawn_ressources(game);
    add_player(game, "sheesh", 0);
    ((player_t *)game->players[0].value)->entity->pos = (pos_t) {0, 0};
    ((player_t *)game->players[0].value)->entity->orientation = (pos_t) {1, 0};
    printf("%d\n", ((player_t *)game->players[0].value)->entity->orientation.x);
    ((player_t *)game->players[0].value)->entity->level = 1;
    game->map->tiles[0][1].ressources[0] = 1;
    char *test = look(game, *(player_t *)game->players[0].value);

    server_t *server = server_new(argc, argv);
    int status = server_run(server);
    server_destroy(server);
    return status;
}
