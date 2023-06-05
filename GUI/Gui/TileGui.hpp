/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** TileGui
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

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
