/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Menu
*/

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Menu {
    public:
        Menu();
        ~Menu();
        void run();
        void display();
        void event();
        sf::RenderWindow *getWindow() const {return _window;};
        std::string getMachine() const {return _machine;};
        int getPort() const {return _portConnect;};

    private:
        sf::RenderWindow *_window;
        sf::Font _font;
        sf::Text _text1;
        sf::Text _text2;
        sf::Text _textMachine;
        sf::Text _textPort;
        sf::Text _textButton;
        sf::RectangleShape _box1;
        sf::RectangleShape _box2;
        std::string _machine;
        std::string _port;
        int _portConnect;

        sf::Sprite _button;
        sf::Texture _textureButton;
        sf::IntRect _rectButton;

        bool _connected;

        int _positionWrite = 0;
};
