
#pragma once
#include "list.h"
#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

//macro that return the position of the tile in the map, if the position is out of the map, it will return the position of the tile on the other side of the map
#define GET_POS(pos, max_pos) (pos.x = pos.x % max_pos.x, pos.y = pos.y % max_pos.y)
#define SEND_POS(pos, max_pos) (pos.y = max_pos.y - pos.y - 1)

#define LEFT 1
#define RIGHT 2
//minerals define

typedef enum mineral_e {
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} mineral_t;

#define FOOD_DENSITY 0.5
#define LINEMATE_DENSITY 0.3
#define DERAUMERE_DENSITY 0.15
#define SIBUR_DENSITY 0.1
#define MENDIANE_DENSITY 0.1
#define PHIRAS_DENSITY 0.08
#define THYSTAME_DENSITY 0.05

//end of minerals define

typedef int fd_t;

//mineral access define
#define ress game->map->tiles[y][x].ressources
#define ress_player player->entity->minerals

//start map_definition structures
typedef struct pos {
    int x;
    int y;
} pos_t;

typedef struct map_tile {
    int *ressources;
    int player_id;
} map_tile_t;

typedef struct map {
    pos_t size;
    map_tile_t **tiles;
} map_t;

//end of map_definition structures

//start of player_definition structures

typedef struct entity {
    pos_t pos;
    int level;
    pos_t orientation;
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
    int freq;
    char buffer[BUFSIZ / 2];
    char send_message[BUFSIZ];
} game_t;

//map handling functions
int normalize(int x, int x_max);
game_t *init_game(option_t *opt);
map_t *init_map(int width, int height);
int *init_ressources();
game_t *add_player(game_t *game, team_name_t team_name, int fd);
game_t *add_team(game_t *game, int max_players, team_name_t name);
team_t *get_team(game_t *game, const char *team_name);
int get_orientation(player_t * player);
int get_from_orientation(player_t * player);

//ressource handling functions
game_t *spawn_ressources(game_t *game);
int get_ressource(game_t *game, int x, int y, int index);
int get_map_ressources(game_t *game, int index);
char *get_ressource_name(game_t *game, char *ressource_in, int x, int y);


//debug functions
void print_ressources(game_t *game);

//ai commandes functions located in ai_commandes.c
const char *look(game_t *game, player_t *player, const char *arg);
const char *move_forward(game_t *game, player_t *player, const char *arg);
const char *turn_left(game_t *game, player_t *player, const char *arg);
const char *turn_right(game_t *game ,player_t *player, const char *arg);
const char *team_unused_slots(game_t *game, player_t *player, const char *arg);
int check_death(game_t *game);
const char *get_inventory(game_t *game, player_t *player, const char *arg);
const char *resolve_incantation(game_t *game, player_t *player, const char *arg);
const char *verif_incantation(game_t *game, player_t *player, const char *arg);
const char *take_object(game_t *game, player_t *player, const char *arg);
const char *drop_object(game_t *game, player_t *player, const char *arg);
const char *eject_player(game_t *game, player_t *player, const char *arg);
//end of ai commandes functions

player_t *get_player_by_fd(game_t *game, int fd);

//gui commandes functions located in gui_commandes.c
char *gui_map_size(game_t *game);
char *gui_map_content(game_t *game);
char *gui_tile_content(game_t *game, int x, int y);
char *gui_team_names(game_t *game);
char *gui_player_connexion(game_t *game, player_t *player);
char *gui_player_position(game_t *game, player_t *player);
char *gui_player_level(game_t *game, player_t *player);
char *gui_player_inventory(game_t *game, player_t *player);
const char *gui_pex(game_t *game, player_t *target);
// player broadcast
const char *gui_pbc(game_t *game, fd_t from, const char *message);
// player incantation
const char *gui_pic(game_t *game, player_t *first, player_t *casters[]);
// player incantation end
const char *gui_pie(game_t *game, player_t *player, int result);
// player fork
const char *gui_pfk(game_t *game, player_t *player);
// player drop ressource
const char *gui_pdr(game_t *game, player_t *player, mineral_t resource);
// player take ressource
const char *gui_pgt(game_t *game, player_t *player, mineral_t resource);
// player death
const char *gui_pdi(game_t *game, player_t *player);
// player egg laying
const char *gui_enw(game_t *game, player_t *player, int egg_id);
// player connection to egg
const char *gui_ebo(game_t *game, int egg_id);
// egg death
const char *gui_edi(game_t *game, int egg_id);
// time unit request
const char *gui_sgt(game_t *game);
// time unit modification
const char *gui_sst(game_t *game);
// end of game
const char *gui_seg(game_t *game, const char *team_name);
// server message
const char *gui_smg(game_t *game, const char *message);
// server unknown command
const char *gui_suc(game_t *game);
// server command parameter
const char *gui_sbp(game_t *game);

void gui_send_all(game_t *game, const char *msg);
void gui_request_process(game_t *game, player_t *sender, const char *body);
