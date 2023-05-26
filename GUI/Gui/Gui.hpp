/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Gui
*/

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include "Data.hpp"

class Gui {
    public:
        Gui(Data *data);
        ~Gui();
        void run();

    private:
        int _port;
        std::string _machine;
        sf::RenderWindow _window;
        sf::View _view;

        Data *_data;
};
