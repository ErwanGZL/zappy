
#pragma once
#include "list.h"
#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//macro that return the position of the tile in the map, if the position is out of the map, it will return the position of the tile on the other side of the map
#define GET_POS(pos, max_pos) (pos.x = pos.x % max_pos.x, pos.y = pos.y % max_pos.y)
#define SEND_POS(pos, max_pos) (pos.y = max_pos.y - pos.y - 1)

//minerals define

#define LINEMATE 0
#define DERAUMERE 1
#define SIBUR 2
#define MENDIANE 3
#define PHIRAS 4
#define THYSTAME 5

#define FOOD_DENSITY 0.5
#define LINEMATE_DENSITY 0.3
#define DERAUMERE_DENSITY 0.15
#define SIBUR_DENSITY 0.1
#define MENDIANE_DENSITY 0.1
#define PHIRAS_DENSITY 0.08
#define THYSTAME_DENSITY 0.05

//end of minerals define

//start map_definition structures
typedef struct pos {
    int x;
    int y;
} pos_t;

typedef struct map_tile {
    int food;
    int *minerals;
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
    int *minerals;
    int food_left;
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
int *init_minerals();
game_t *add_player(game_t *game, team_name_t team_name, int fd);
game_t *add_team(game_t *game, int max_players, team_name_t name);
team_t **get_team(game_t *game, team_name_t team_name);

//ressource handling functions
game_t *spawn_ressources(game_t *game);
int get_ressource(game_t *game, int x, int y, int index);
int get_map_ressources(game_t *game, int index);