/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Data
*/

#pragma once
#include <vector>
#include <iostream>

#include "Tile.hpp"
#include "Team.hpp"
#include "Player.hpp"
#include "Egg.hpp"
#include "enum.hpp"
#include <mutex>

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
        int getTimeUnit();
        void addPlayer(int id, int x, int y, Orientation orientation, int level, std::string team);
        void addEgg (int id, int x, int y, std::string team);
        void removePlayer(int id);
        void removeEgg(int id);
        std::vector<Player*> getPlayers();
        std::vector<Egg*> getEggs();
        std::vector<Team*> getTeams();
        Player *getPlayerById(int id);
        Egg *getEggById(int id);
        std::vector<Player*> getPlayersByCoords(int x, int y);
        void lock() {_mutex.lock();};
        void unlock() {_mutex.unlock();};
        void setMachine(std::string machine) {_machine = machine;};
        void setPort(int port) {_port = port;};
        std::string getMachine() {return _machine;};
        int getPort() {return _port;};

    private:
        std::vector<std::vector<Tile*>> _map;
        std::vector<Team*> _teams;
        std::vector<Player*> _players;
        std::vector<Egg*> _eggs;
        std::string _machine = "";
        int _port = -1;
        int _width = -1;
        int _height = -1;
        int _timeUnit = 0;
        std::mutex _mutex;

};
