/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Data
*/

#pragma once
#include <vector>

#include "Tile.hpp"
#include "Team.hpp"
#include "Player.hpp"
#include "enum.hpp"

class Data {
    public:
        Data();
        ~Data();
        void createMap(int width, int height);
        std::vector<std::vector<Tile*>> getMap();
        int getWidth();
        int getHeight();
        void setMap(int x, int y, std::vector<int> ressources);
        void addTeam(std::string name);
        void setTimeUnit(int timeUnit);
        void addPlayer(int id, int x, int y, Orientation orientation, int level, std::string team);
        Player *getPlayerById(int id);

    private:
        std::vector<std::vector<Tile*>> _map;
        std::vector<Team*> _teams;
        std::vector<Player*> _players;
        int _width = 0;
        int _height = 0;
        int _timeUnit = 0;

};
