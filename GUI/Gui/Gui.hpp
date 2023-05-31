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
#include <climits>
#include <cstdlib>

struct playerSprite_s {
    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect rect;
    sf::Clock clock;
    bool isMoving = false;
    int frame = 0;
    int nbFrame = 0;
    int id = 0;
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

        std::vector<tileData_s*> _map;
        std::vector<playerSprite_s*> _players;
        sf::IntRect getRect(int x, int y, std::vector<std::vector<int>> map);
        sf::IntRect getRectBorder(int x, int y, int *rotate);

        Data *_data;
};
