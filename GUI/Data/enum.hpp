/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** enum
*/

#pragma once

enum Ressources {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
};

enum Orientation {
    NORTH = 1,
    EAST = 2,
    SOUTH = 4,
    WEST = 8,
    NORTH_EAST = 16,
    SOUTH_EAST = 32,
    SOUTH_WEST = 64,
    NORTH_WEST = 128
};

enum PlayerStatus {
    NONE,
    INCANTATION,
    DEAD,
    LAYING
};
