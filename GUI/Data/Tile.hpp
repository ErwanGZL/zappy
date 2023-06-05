/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Tile
*/

#pragma once
#include <vector>
#include <iostream>

class Tile {
    public:
        Tile();
        ~Tile();
        void setRessources(std::vector<int> ressources);
        std::vector<int> getRessources();
    private:
        std::vector<int> _ressources = {0, 0, 0, 0, 0, 0, 0};
};
