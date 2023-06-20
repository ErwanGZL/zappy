/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Menu
*/

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Sound.hpp"


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
        int getMusicVolume() {return _musicBar->getVolume();};
        int getEffectVolume() {return _effectsBar->getVolume();};
        sf::Music *getMusic() {return _music;};

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
        std::string _machine = "127.0.0.1";
        std::string _port = "4242";
        int _portConnect;

        sf::Sprite _button;
        sf::Texture _textureButton;

        sf::Sprite _background;
        sf::Texture _textureBackground;
        sf::Clock _clock;

        bool _connected;

        int _positionWrite = 1;

        sf::Music *_music;

        Sound *_effectsBar;
        Sound *_musicBar;
};
