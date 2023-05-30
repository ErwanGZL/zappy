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

struct playerSprite_s {
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    sf::IntRect rect;
    sf::Clock clock;
    int frame = 0;
    int nbFrame = 0;
    int id = 0;
    std::string team;
    Orientation orientation;
};

struct tileData_s {
    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect rect;
    sf::Clock clock;
    int frame = 0;
    int nbFrame = 0;
    int id = 0;
};

class Gui {
    public:
        Gui(Data *data);
        ~Gui();
        void run();
        void generateMap();

    private:
        int _port;
        std::string _machine;
        sf::RenderWindow _window;
        sf::View _view;
        sf::Font _font;
        sf::Clock _clock;

        std::vector<std::vector<tileData_s*>> _map;
        sf::IntRect getRect(int x, int y, std::vector<std::vector<int>> map);

        Data *_data;
};
