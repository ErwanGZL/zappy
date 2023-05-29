/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Egg
*/

#include "Egg.hpp"

Egg::Egg(int id, int x, int y, std::string teamName)
    : _id(id), _x(x), _y(y), _teamName(teamName)
{
}

Egg::~Egg()
{
}

int Egg::getId()
{
    return _id;
}

int Egg::getX()
{
    return _x;
}

int Egg::getY()
{
    return _y;
}

std::string Egg::getTeamName()
{
    return _teamName;
}
