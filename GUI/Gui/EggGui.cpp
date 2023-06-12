/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** EggGui
*/

#include "EggGui.hpp"

EggGui::EggGui(Data *data, sf::Texture *texture)
{
    _data = data;
    _texture = texture;
    _sprite.setTexture(*_texture);
    _sprite.setTextureRect(sf::IntRect(32, 16 * 27, 16, 16));
    _sprite.setOrigin(8, 8);
}

EggGui::~EggGui()
{
}

void EggGui::update()
{

}

void EggGui::draw(sf::RenderWindow *window)
{
    for (auto &egg : _data->getEggs()) {
        _sprite.setPosition(egg->getX() * 16, egg->getY() * 16);
        window->draw(_sprite);
    }
}

