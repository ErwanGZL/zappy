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
#include "Perlin.hpp"
#include "TileGui.hpp"
#include "PlayerGui.hpp"
#include <climits>
#include <cstdlib>

class Gui {
    public:
        Gui(Data *data);
        ~Gui();
        void run();
        void generateMap();
        void generatePlayer();
        void updateData();
        void displayMap();
        void displayPlayer();
        void animate();

    private:
        int _port;
        std::string _machine;
        sf::RenderWindow _window;
        sf::View _viewGlobal;
        sf::Font _font;

        sf::Texture _textureMap;
        sf::Texture _texturePlayer;

        std::vector<TileGui*> _map;
        std::vector<PlayerGui*> _players;
        sf::IntRect getRect(int x, int y, std::vector<std::vector<int>> map);
        sf::IntRect getRectBorder(int x, int y, int *rotate);

        Data *_data;
};
