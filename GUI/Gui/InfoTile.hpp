/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** InfoTile
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Data.hpp"
#include "enum.hpp"


class InfoTile {
    public:
        InfoTile(Data *data);
        ~InfoTile();
        void draw(sf::RenderWindow &window);
        void update();
        void setMouse (sf::RenderWindow &window, sf::Event event);

    protected:
    private:
        Data *_data;
        bool _isToggled = true;
        sf::RectangleShape _background;
        sf::RectangleShape _overlay;
        sf::Text _text;
        sf::Font _font;
        sf::Texture _texture;
        sf::Sprite _sprite;
        int _x = 0;
        int _y = 0;
        sf::View _view;

};
