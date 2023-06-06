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
    server_t *server = server_new(argc, argv);
    game_t *a = init_game(server->options);
    add_player(a, "test", 0);
    char *test = get_inventory(getPlayerByFd(a, 0));
    printf("%s\n", test);
    int status = server_run(server);
    server_destroy(server);
    return status;
}
