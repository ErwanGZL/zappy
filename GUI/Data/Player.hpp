/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Player
*/

#pragma once
#include <vector>
#include <string>
#include "enum.hpp"

class Player {
    public:
        Player();
        ~Player();
        void setRessources(std::vector<int> ressources);
        void addLevel();
        void setLevel(int level);
        void setId(int id);
        void setX(int x);
        void setY(int y);
        void setOrientation(Orientation orientation);
        void setTeamName(std::string teamName);
        void broadcast(std::string message);
        void setStatus(PlayerStatus status);
        PlayerStatus getStatus();

        std::vector<int> getRessources();
        int getLevel();
        int getId();
        int getX();
        int getY();
        Orientation getOrientation();
        std::string getTeamName();

    private:
        std::vector<int> _ressources = {0, 0, 0, 0, 0, 0, 0};
        int _level = 0;
        int _id = 0;
        int _x = 0;
        int _y = 0;
        Orientation _orientation;
        std::string _teamName = "";
        std::string _message = "";
        PlayerStatus _status = PlayerStatus::NONE;
};
