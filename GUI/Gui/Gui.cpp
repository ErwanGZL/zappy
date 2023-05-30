/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Gui
*/

#include "Gui.hpp"
#include <iostream>
#include <unistd.h>
#include <random>
#include <math.h>

void *threadGui(void *arg)
{
    Gui *gui = new Gui((Data *)arg);
    gui->run();
    return (NULL);
}

Gui::Gui(Data *data)
{
    _data = data;
    _window.create(sf::VideoMode(720, 480), "Zappy");
    _window.setFramerateLimit(60);
    _view = _window.getDefaultView();
}

Gui::~Gui()
{
}

void Gui::run ()
{
    _clock.restart();
    generateMap();

    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
        _window.clear(sf::Color::Black);
        for (int i = 0; i < _map.size(); i++) {
            for (int j = 0; j < _map[i].size(); j++) {
                _window.draw(_map[i][j]->sprite);
            }
        }
        _window.display();
    }
}

void Gui::generateMap()
{
    int width = _data->getWidth();
    int height = _data->getHeight();
    Perlin perlin(width, height);
    std::vector<std::vector<int>> noiseMap = perlin.run();
    for (int i = 0; i < noiseMap.size() ; i++) {
        std::vector<tileData_s*> line;
        for (int j = 0; j < noiseMap[i].size(); j++) {
            tileData_s *tile = new tileData_s;
            tile->texture.loadFromFile("GUI/sprites/map.png");
            tile->rect = getRect(i, j, noiseMap);
            tile->sprite.setTexture(tile->texture);
            tile->sprite.setTextureRect(tile->rect);
            tile->sprite.setPosition(j * 16, i * 16);
            line.push_back(tile);
        }
        _map.push_back(line);
    }
}

sf::IntRect Gui::getRect(int x, int y, std::vector<std::vector<int>> mappa)
{
    sf::Vector2i pos;
    int id = mappa[x][y];
    std::vector<int> border = {
        WEST | NORTH,
        NORTH,
        NORTH | EAST,
        WEST | NORTH | EAST,
        WEST | NORTH | SOUTH_EAST,
        NORTH | EAST | SOUTH_WEST,
        WEST,
        EAST,
        WEST | EAST,
        WEST | SOUTH | NORTH_EAST,
        EAST | SOUTH | NORTH_WEST,
        WEST | SOUTH,
        SOUTH,
        SOUTH | EAST,
        WEST | SOUTH | EAST,
        SOUTH_EAST,
        SOUTH_WEST,
        WEST | NORTH | SOUTH,
        NORTH | SOUTH,
        NORTH | SOUTH | EAST,
        WEST | NORTH | SOUTH | EAST,
        NORTH_EAST,
        NORTH_WEST
    };
    if (id == 0) {
        int random = rand() % 2;
        if (random == 0)
            pos = sf::Vector2i(0, 0);
        else
            pos = sf::Vector2i(0, 16 * 5);
    } else if (id == 1) {
        int iy = 16 * 4;
        int orient = 0;
        if (x > 0 && mappa[x - 1][y] != id) {
            orient |= NORTH;
        }
        if (x < mappa.size() - 1 && mappa[x + 1][y] != id)
            orient |= SOUTH;
        if (y > 0 && mappa[x][y - 1] != id)
            orient |= WEST;
        if (y < mappa[x].size() - 1 && mappa[x][y + 1] != id)
            orient |= EAST;
        for (int i = 0; i < border.size(); i++) {
            if (orient == border[i]) {
                pos = sf::Vector2i(16 * i, iy);
                break;
            }
        }
        if (orient == 0) {
            int random = rand() % 14;
            iy = 16 * 2;
            pos = sf::Vector2i(16 * random, iy);
        }
    } else if (id == 2) {
        int x = 16 * (rand() % 10);
        int y = 16 * 3;
        pos = sf::Vector2i(x, y);
    }
    return (sf::IntRect(pos.x, pos.y, 16, 16));
}
