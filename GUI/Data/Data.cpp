/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Data
*/

#include "Data.hpp"

Data::Data()
{
}

Data::~Data()
{
}

void Data::createMap(int width, int height)
{
    _width = width;
    _height = height;
    for (int i = 0; i < height; i++) {
        std::vector<Tile*> line;
        for (int j = 0; j < width; j++) {
            Tile *tile;
            line.push_back(tile);
        }
        _map.push_back(line);
    }
}

std::vector<std::vector<Tile*>> Data::getMap()
{
    return _map;
}

int Data::getWidth()
{
    return _width;
}

int Data::getHeight()
{
    return _height;
}

void Data::setMap(int x, int y, std::vector<int> ressources)
{
    _map[y][x]->setRessources(ressources);
}

void Data::addTeam(std::string name)
{
    Team *team = new Team();
    team->setName(name);
    _teams.push_back(team);
}

void Data::setTimeUnit(int timeUnit)
{
    _timeUnit = timeUnit;
}

void Data::addPlayer(int id, int x, int y, Orientation orientation, int level, std::string team)
{
    Player *player = new Player();
    player->setId(id);
    player->setX(x);
    player->setY(y);
    player->setOrientation(orientation);
    player->setLevel(level);
    player->setTeamName(team);
    _players.push_back(player);
}

Player *Data::getPlayerById(int id)
{
    for (int i = 0; i < _players.size(); i++) {
        if (_players[i]->getId() == id)
            return _players[i];
    }
    return NULL;
}
