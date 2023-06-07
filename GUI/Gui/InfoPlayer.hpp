/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** InfoPlayer
*/

#pragma once
#include "Data.hpp"
#include "InfoTeam.hpp"
#include <SFML/Graphics.hpp>


class InfoPlayer {
    public:
        InfoPlayer(Data *data);
        ~InfoPlayer();
        void update();
        void draw(sf::RenderWindow &window);
        void setMouse(sf::RenderWindow &window, sf::Event event, sf::View view);
    protected:
    private:
        Data *_data;
        sf::RectangleShape _button;
        sf::Sprite _sprite;
        std::vector<InfoTeam *> _teams;
        sf::View _view;
        sf::Texture _texture;
        int _display = 0;
};
