#pragma once

#include "list.h"

typedef struct {
    int port;
    int width;
    int height;
    list_t teams;
    int clientsNb;
    double freq;
} zserv_opt_t;
