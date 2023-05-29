/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Tile
*/

#include "Tile.hpp"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::setRessources(std::vector<int> ressources)
{
    _ressources = ressources;
}

std::vector<int> Tile::getRessources()
{
    return _ressources;
}