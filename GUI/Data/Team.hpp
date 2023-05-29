/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Team
*/

#pragma once
#include <vector>
#include <string>

class Team {
    public:
        Team();
        ~Team();
        void setName(std::string name);
        void setSlots(int slots);
        std::string getName();
        int getSlots();

    private:
        std::string _name;
        int _slots = 0;
};
