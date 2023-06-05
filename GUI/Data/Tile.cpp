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
    _ressources.clear();
    for (int i = 0; i < ressources.size(); i++) {
        _ressources.push_back(ressources[i]);
    }
    // for (int i = 0; i < _ressources.size(); i++) {
    //     std::cout << _ressources[i] << std::endl;
    // }
}

std::vector<int> Tile::getRessources()
{
    return _ressources;
}