/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** InfoTeam
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Data.hpp"

class InfoTeam {
    public:
        InfoTeam(Data *data, sf::Texture texture, std::string name, int nb);
        ~InfoTeam();
        void update();
        void draw(sf::RenderWindow &window, int display);
        void setMouse(sf::RenderWindow &window, sf::Event event, sf::View view);

    private:
        Data *_data;
        sf::RectangleShape _background;
        sf::Text _text;
        sf::Font _font;
        sf::Texture _texture;
        sf::Sprite _sprite;
        int _x = 0;
        int _y = 0;
        std::string _name;
        int _numberOfPlayers = 0;
        int _teamNumber = 0;
        sf::View _view;
};
