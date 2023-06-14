/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu()
{
    _window = new sf::RenderWindow(sf::VideoMode(720, 480), "Zappy");
    _window->setFramerateLimit(60);
    _font.loadFromFile("GUI/font/monogram.ttf");
    _text1.setFont(_font);
    _text1.setString("Machine");
    _text1.setCharacterSize(50);
    _text1.setFillColor(sf::Color::Black);
    _text1.setPosition(720 / 2, 480 / 2 - 200);
    _text1.setOrigin(_text1.getGlobalBounds().width / 2, _text1.getGlobalBounds().height / 2);
    _text2.setFont(_font);
    _text2.setString("Port");
    _text2.setCharacterSize(50);
    _text2.setFillColor(sf::Color::Black);
    _text2.setPosition(720 / 2, 480 / 2 - 50);
    _text2.setOrigin(_text2.getGlobalBounds().width / 2, _text2.getGlobalBounds().height / 2);
    _textMachine.setFont(_font);
    _textMachine.setString(_machine);
    _textMachine.setCharacterSize(50);
    _textMachine.setFillColor(sf::Color::White);
    _textMachine.setPosition(720 / 2, 480 / 2 - 150);
    _textPort.setFont(_font);
    _textPort.setString(_port);
    _textPort.setCharacterSize(50);
    _textPort.setFillColor(sf::Color::White);
    _textPort.setPosition(720 / 2, 480 / 2);
    _box1.setSize(sf::Vector2f(500, 100));
    _box1.setFillColor(sf::Color(0, 0, 0, 200));
    _box1.setPosition(720 / 2, 480 / 2 - 150);
    _box1.setOrigin(_box1.getGlobalBounds().width / 2, _box1.getGlobalBounds().height / 2);
    _box2.setSize(sf::Vector2f(500, 100));
    _box2.setFillColor(sf::Color(0, 0, 0, 200));
    _box2.setPosition(720 / 2, 480 / 2);
    _box2.setOrigin(_box2.getGlobalBounds().width / 2, _box2.getGlobalBounds().height / 2);

    _textureButton.loadFromFile("GUI/sprites/button.png");
    _button.setTexture(_textureButton);
    _button.setTextureRect(sf::IntRect(0, 0, 22, 16));
    _button.setPosition(720 / 2, 480 / 2 + 200);
    _button.setOrigin(_button.getGlobalBounds().width / 2, _button.getGlobalBounds().height / 2);
    _button.setScale(5, 5);

    _textButton.setFont(_font);
    _textButton.setString("Connect");
    _textButton.setCharacterSize(50);
    _textButton.setFillColor(sf::Color::Black);
    _textButton.setPosition(720 / 2, 480 / 2 + 200);
    _textButton.setOrigin(_textButton.getGlobalBounds().width / 2, _textButton.getGlobalBounds().height / 2);
}

Menu::~Menu()
{
}

void Menu::run()
{
    while (_window->isOpen()) {
        event();
        display();
        if (_connected == true)
            break;
    }
}

void Menu::display()
{
    _window->clear(sf::Color::Blue);
    _window->draw(_box1);
    _window->draw(_box2);
    _window->draw(_text1);
    _window->draw(_text2);
    _window->draw(_textMachine);
    _window->draw(_textPort);
    _window->draw(_button);
    _window->display();
}

void Menu::event()
{
    sf::Event event;
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window->close();
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8 && _machine.size() > 0 && _positionWrite == 1)
                _machine.pop_back();
            else if (event.text.unicode == 8 && _port.size() > 0 && _positionWrite == 2)
                _port.pop_back();
            else if (event.text.unicode < 128 && _machine.size() < 20 && _positionWrite == 1)
                _machine += static_cast<char>(event.text.unicode);
            else if (event.text.unicode < 128 && _port.size() < 20 && _positionWrite == 2)
                _port += static_cast<char>(event.text.unicode);
        }
        if (_button.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*_window)))) {
            _textButton.setFillColor(sf::Color::White);
            if (event.type == sf::Event::MouseButtonPressed) {
                _button.setTextureRect(sf::IntRect(22, 0, 22, 16));
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                _connected = true;
            }
        } else {
            _textButton.setFillColor(sf::Color::Black);
            _button.setTextureRect(sf::IntRect(0, 0, 22, 16));
        }
        if (_box1.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*_window)))) {
            if (event.type == sf::Event::MouseButtonPressed) {
                _positionWrite = 1;
            }
        }
        if (_box2.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*_window)))) {
            if (event.type == sf::Event::MouseButtonPressed) {
                _positionWrite = 2;
            }
        }
    }
}


