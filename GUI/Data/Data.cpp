/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Data
*/

#include "Data.hpp"

Data::Data()
{
    _semaphore = sem_t();
}

Data::~Data()
{
    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            Tile *tile = _map[i][j];
            _map[i].erase(_map[i].begin() + j);
            delete tile;
        }
    }
    for (int i = 0; i < _players.size(); i++) {
        Player *player = _players[i];
        _players.erase(_players.begin() + i);
        delete _players[i];
    }
    for (int i = 0; i < _eggs.size(); i++) {
        Egg *egg = _eggs[i];
        _eggs.erase(_eggs.begin() + i);
        delete _eggs[i];
    }
    for (int i = 0; i < _teams.size(); i++) {
        Team *team = _teams[i];
        _teams.erase(_teams.begin() + i);
        delete _teams[i];
    }
}

void Data::createMap(int width, int height)
{
    _width = width;
    _height = height;
    for (int i = 0; i < height; i++) {
        std::vector<Tile*> line;
        for (int j = 0; j < width; j++) {
            Tile *tile = new Tile();
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

void Data::removePlayer(int id)
{
    std::vector<int> ids;
    for (int i = 0; i < _players.size(); i++) {
        if (_players[i]->getId() == id) {
            ids.push_back(i);
        }
    }
    for (int i = 0; i < ids.size(); i++) {
        // Player *player = _players[ids[i]];
        _players.erase(_players.begin() + ids[i]);
        // delete player;
    }
}

void Data::addEgg(int id, int x, int y, std::string team)
{
    Egg *egg = new Egg(id, x, y, team);
    _eggs.push_back(egg);
}

Egg *Data::getEggById(int id)
{
    for (int i = 0; i < _eggs.size(); i++) {
        if (_eggs[i]->getId() == id)
            return _eggs[i];
    }
    return NULL;
}

void Data::removeEgg(int id)
{
    for (int i = 0; i < _eggs.size(); i++) {
        if (_eggs[i]->getId() == id) {
            Egg *egg = _eggs[i];
            _eggs.erase(_eggs.begin() + i);
            delete egg;
        }
    }
}

std::vector<Player*> Data::getPlayersByCoords(int x, int y)
{
    std::vector<Player*> players;
    for (int i = 0; i < _players.size(); i++) {
        if (_players[i]->getX() == x && _players[i]->getY() == y)
            players.push_back(_players[i]);
    }
    return players;
}

int Data::getTimeUnit()
{
    return _timeUnit;
}

std::vector<Player*> Data::getPlayers()
{
    return _players;
}

std::vector<Egg*> Data::getEggs()
{
    return _eggs;
}

std::vector<Team*> Data::getTeams()
{
    return _teams;
}
