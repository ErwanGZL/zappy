
#pragma once
#include "stdio.h"

#define GET_POS(pos, max_pos) (pos.x = pos.x % max_pos.x, pos.y = pos.y % max_pos.y)

typedef struct pos {
    int x;
    int y;
} pos_t;

typedef struct map_tile {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} map_tile_t;

typedef struct map {
    int width;
    int height;
    map_tile_t **tiles;
} map_t;

int game();

