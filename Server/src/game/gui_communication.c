#include "game.h"

char *gui_map_size(game_t *game)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "msz %d %d\n", game->map->size.x, game->map->size.y);
    return game->send_message;
}

char *gui_tile_content(game_t *game, int x, int y)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "bct %d %d %d %d %d %d %d %d %d\n", x, y, ress[0], ress[1], ress[2], ress[3], ress[4], ress[5], ress[6]);
    return game->send_message;
}

char *gui_map_content(game_t *game)
{
    memset(game->buffer, 0, BUFSIZ / 2);
    memset(game->send_message, 0, BUFSIZ);
    for (int y = 0; y < game->map->size.y; y++)
    {
        for (int x = 0; x < game->map->size.x; x++)
        {
            memcpy(game->buffer, game->send_message, strlen(game->send_message));
            sprintf(game->send_message, "%sbct %d %d %d %d %d %d %d %d %d\n", game->buffer, x, y, ress[0], ress[1], ress[2], ress[3], ress[4], ress[5], ress[6]);
            memset(game->buffer, 0, BUFSIZ / 2);
        }
    }
    return game->send_message;
}

char *gui_team_names(game_t *game)
{
    memset(game->send_message, 0, BUFSIZ);
    memset(game->buffer, 0, BUFSIZ / 2);
    for (list_t ptr = game->teams; ptr != NULL; ptr = ptr->next)
    {
        memcpy(game->buffer, game->send_message, strlen(game->send_message));
        sprintf(game->send_message, "%stna %s\n", game->buffer, ((team_t *)ptr->value)->name);
    }
    return game->send_message;
}

char *gui_player_connexion(game_t *game, player_t *player)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "pnw %d %d %d %d %d %s\n", player->fd, player->entity->pos.x, player->entity->pos.y, get_orientation(player), player->entity->level, player->team_name);
    return game->send_message;
}

char *gui_player_position(game_t *game, player_t *player)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "ppo %d %d %d %d\n", player->fd, player->entity->pos.x, player->entity->pos.y, get_orientation(player));
    return game->send_message;
}

char *gui_player_level(game_t *game, player_t *player)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "plv %d %d\n", player->fd, player->entity->level);
    return game->send_message;
}

char *gui_player_inventory(game_t *game, player_t *player)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "pin %d %d %d %d %d %d %d %d %d %d", player->fd, player->entity->pos.x, player->entity->pos.y, player->entity->food_left, ress_player[0], ress_player[1], ress_player[2], ress_player[3], ress_player[4], ress_player[5]);
    return game->send_message;
}

// player expulsion
const char *gui_pex(game_t *game, player_t *target)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "pex %d\n", target->fd);
    return game->send_message;
}

// player broadcast
const char *gui_pbc(game_t *game, fd_t from, const char *message)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "pbc %d %s\n", from, message);
    return game->send_message;
}

// player incantation
const char *gui_pic(game_t *game, player_t *first, player_t *casters[])
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message,
            "pic %d %d %d %d",
            first->entity->pos.x,
            first->entity->pos.y,
            first->entity->level + 1,
            first->fd);
    for (int i = 0; casters[i] != NULL; i++)
        sprintf(game->send_message, "%s %d", game->send_message, casters[i]->fd);
    strcat(game->send_message, "\n");
    return game->send_message;
}

// player incantation end
const char *gui_pie(game_t *game, player_t *player, int result)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message,
            "pie %d %d %d\n",
            player->entity->pos.x,
            player->entity->pos.y,
            result);
    return game->send_message;
}

// player fork
const char *gui_pfk(game_t *game, player_t *player)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "pfk %d\n", player->fd);
    return game->send_message;
}

// player drop ressource
const char *gui_pdr(game_t *game, player_t *player, mineral_t resource)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "pdr %d %d\n", player->fd, resource + 1);
    return game->send_message;
}

// player take ressource
const char *gui_pgt(game_t *game, player_t *player, mineral_t resource)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "pgt %d %d\n", player->fd, resource + 1);
    return game->send_message;
}

// player death
const char *gui_pdi(game_t *game, player_t *player)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "pdi %d\n", player->fd);
    return game->send_message;
}

// player egg laying
const char *gui_enw(game_t *game, player_t *player, int egg_id)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message,
            "enw %d %d %d %d\n",
            egg_id,
            player->fd,
            player->entity->pos.x,
            player->entity->pos.y);
    return game->send_message;
}

// player connection to egg
const char *gui_ebo(game_t *game, int egg_id)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "ebo %d\n", egg_id);
    return game->send_message;
}

// egg death
const char *gui_edi(game_t *game, int egg_id)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "edi %d\n", egg_id);
    return game->send_message;
}

// time unit request
const char *gui_sgt(game_t *game)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "sgt %d\n", game->freq);
    return game->send_message;
}

// time unit modification
const char *gui_sst(game_t *game)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "sst %d\n", game->freq);
    return game->send_message;
}

// end of game
const char *gui_seg(game_t *game, const char *team_name)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "seg %s\n", team_name);
    return game->send_message;
}

// server message
const char *gui_smg(game_t *game, const char *message)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "smg %s\n", message);
    return game->send_message;
}

// server unknown command
const char *gui_suc(game_t *game)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "suc\n");
    return game->send_message;
}

// server command parameter
const char *gui_sbp(game_t *game)
{
    memset(game->send_message, 0, BUFSIZ);
    sprintf(game->send_message, "sbp\n");
    return game->send_message;
}
