/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** TileGui
*/

#include "TileGui.hpp"

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
