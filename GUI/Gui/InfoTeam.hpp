/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** InfoTeam
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Data.hpp"
#include "PlayerGui.hpp"

class InfoTeam {
    public:
        InfoTeam(Data *data, sf::Texture texture, std::string name, int nb);
        ~InfoTeam();
        void update();
        void draw(sf::RenderWindow &window, int display);
        bool setMouse(sf::RenderWindow &window, sf::Event event, sf::View view);
        void unToggle() {_clicked = false;};
        bool getClicked() {return _clicked;};
        sf::View getView(std::vector<PlayerGui *> player);

    private:
        Data *_data;
        sf::RectangleShape _background;
        sf::RectangleShape _hoover;
        sf::RectangleShape _backgroundPlayer;
        sf::RectangleShape _backgroundText;
        sf::Text _textPlayer;
        sf::Text _textPlayer2;
        sf::Text _textPlayer3;
        sf::Text _text;
        sf::Font _font;
        sf::Texture _texture;
        sf::Texture _texturePlayer;
        sf::Sprite _sprite;
        sf::Sprite _spritePlayer;
        int _x = 0;
        int _y = 0;
        std::string _name;
        int _numberOfPlayers = 0;
        int _teamNumber = 0;
        sf::View _view;
        int _display = 0;

        bool _clicked = false;
        int _index = 0;
        int _broadcast = 0;
};
