/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Sound
*/

#pragma once
#include <SFML/Graphics.hpp>

class Sound {
    public:
        Sound(std::string str, int x, int y, int base, int max = 100);
        ~Sound();
        int getVolume();
        void event(sf::Event event, sf::RenderWindow *window);
        void draw(sf::RenderWindow *window);
        void setPos(int x, int y);

    private:
        sf::RectangleShape _box1;
        sf::RectangleShape _box2;
        sf::Sprite _buttonPlus;
        sf::Sprite _buttonMinus;
        sf::Texture _textureButton;
        sf::Text _text1;
        sf::Text _text2;
        sf::Text _text3;
        sf::Font _font;
        sf::View _view;
        int _x;
        int _y;
        int _volume;
        int _max;
};
