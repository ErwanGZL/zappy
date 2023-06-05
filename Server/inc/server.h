/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** server
*/

#pragma once

#include "list.h"
#include "netctl.h"
#include "options.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

typedef struct {
    option_t *options;
    netctl_t *netctl;
} server_t;

server_t *server_new(int argc, char *argv[]);
void server_select(server_t *server);
void server_destroy(server_t *server);
void server_handshake(server_t *server, int fd);
int server_run(server_t *server);
