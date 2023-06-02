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
    sf::Clock clockAnimate;
    bool isMoving = false;
    int frame = 0;
    int nbFrame = 0;
    int id = 0;
    int stockLeft = 0;
    int left = 0;
};

// struct tileData_s {
//     sf::Sprite sprite;
//     sf::Texture texture;
//     sf::IntRect rect;
//     sf::Clock clock;
//     int frame = 0;
//     int nbFrame = 0;
//     int id = 0;
// };


class TileGui {
    private:
        sf::Sprite _sprite;
        sf::IntRect _rect;
        sf::Texture *_texture;
        sf::Clock _clock;
        int _frame = 0;
        int _nbFrame = 0;
        int _id = 0;

    public:
        TileGui(int x, int y, int id, sf::Texture *texture, sf::IntRect rect, int rotate);
        ~TileGui();
        void update();
        void animate(int timeUnit);
        sf::Sprite getSprite() {return _sprite;};
        int getId() {return _id;};
};

TileGui::TileGui(int x, int y, int id, sf::Texture *texture, sf::IntRect rect, int rotate)
{
    _sprite.setTexture(*texture);
    _sprite.setTextureRect(rect);
    _sprite.setPosition(x, y);
    _sprite.setOrigin(8, 8);
    _sprite.setRotation(rotate);
    _texture = texture;
    _rect = rect;
    _id = id;
    _nbFrame = (rect.top == 16 * 6 || id == 0) ? 3 : 0;
    _frame = 0;
}

TileGui::~TileGui()
{
}

void TileGui::update()
{
    _sprite.setTextureRect(sf::IntRect(_rect.width * _frame, 0, _rect.width, _rect.height));
    _frame++;
    if (_frame >= _nbFrame)
        _frame = 0;
}

void TileGui::animate(int timeUnit)
{
    if (_nbFrame > 0) {
        if (_clock.getElapsedTime().asMilliseconds() > 1000 / timeUnit) {
            _frame++;
            if (_frame >= _nbFrame)
                _frame = 0;
            _rect.left = _frame * 16;
            _sprite.setTextureRect(_rect);
            _clock.restart();
        }
    }
}

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
        int stateTop(int id);

    private:
        int _port;
        std::string _machine;
        sf::RenderWindow _window;
        sf::View _viewGlobal;
        sf::Font _font;

        sf::Texture _textureMap;
        sf::Texture _texturePlayer;

        std::vector<TileGui*> _map;
        std::vector<playerSprite_s*> _players;
        sf::IntRect getRect(int x, int y, std::vector<std::vector<int>> map);
        sf::IntRect getRectBorder(int x, int y, int *rotate);

        Data *_data;
};
