
#pragma once
#include "stdio.h"
#include "list.h"
#include "stdlib.h"

//macro that return the position of the tile in the map, if the position is out of the map, it will return the position of the tile on the other side of the map
#define GET_POS(pos, max_pos) (pos.x = pos.x % max_pos.x, pos.y = pos.y % max_pos.y)

//start map_definition structures
typedef struct pos {
    int x;
    int y;
} pos_t;

typedef struct minerals {
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} minerals_t;

typedef struct map_tile {
    int food;
    minerals_t minerals;
    int player_id;
} map_tile_t;

typedef struct map {
    int width;
    int height;
    map_tile_t **tiles;
} map_t;

//end of map_definition structures

//start of player_definition structures

typedef struct entity {
    pos_t pos;
    int level;
    //int orientation; pos_t orientation; ?
    minerals_t minerals;
} entity_t;

typedef struct player {
    int fd;
    team_name_t team_name;
    entity_t *entity;
} player_t;

typedef struct team {
    team_name_t name;
    int max_players;
    int nb_players;
} team_t;

//end of player_definition structures

//game structure

typedef struct game {
    map_t *map;
    list_t players;
    list_t teams;
    int nb_teams;
    int nb_players;
} game_t;

game_t *init_game(int width, int height);
map_t *init_map(int width, int height);