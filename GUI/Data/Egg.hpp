/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Egg
*/

#pragma once
#include <string>

class Egg {
    public:
        Egg(int id, int x, int y, std::string teamName);
        ~Egg();
        int getId();
        int getX();
        int getY();
        std::string getTeamName();

    private:
        int _id = 0;
        std::string _teamName = "";
        int _x = 0;
        int _y = 0;
};

