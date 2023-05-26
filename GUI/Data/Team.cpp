/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Team
*/

#include "Team.hpp"

Team::Team()
{
}

Team::~Team()
{
}

void Team::setName(std::string name)
{
    _name = name;
}

void Team::setSlots(int slots)
{
    _slots = slots;
}

std::string Team::getName()
{
    return _name;
}

int Team::getSlots()
{
    return _slots;
}
