
#pragma once

#include "list.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

typedef struct sockaddr_in sockaddr_in_t;

typedef struct {
    int fd;
    sockaddr_in_t addr;
} socket_t;

typedef struct {
    fd_set readfds;
    socket_t entrypoint;
    list_t clients;
} netctl_t;

netctl_t *netctl_new(int port);
int netctl_accept(netctl_t *netctl);
void netctl_destroy(netctl_t *netctl);
