/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu() : _musicBar("Music", 720 / 2 - 200, 480 / 2 + 150, 50), _effectsBar("Effects", 720 / 2 + 200, 480 / 2 + 150, 50)
{
    _window = new sf::RenderWindow(sf::VideoMode(720, 480), "Zappy");
    _window->setFramerateLimit(60);
    _font.loadFromFile("GUI/font/monogram.ttf");
    _text1.setFont(_font);
    _text1.setString("Machine");
    _text1.setCharacterSize(50);
    _text1.setFillColor(sf::Color::White);
    _text1.setPosition(720 / 2, 480 / 2 - 200);
    _text1.setOrigin(_text1.getGlobalBounds().width / 2, _text1.getGlobalBounds().height / 2);
    _text2.setFont(_font);
    _text2.setString("Port");
    _text2.setCharacterSize(50);
    _text2.setFillColor(sf::Color::White);
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
    _box1.setSize(sf::Vector2f(500, 50));
    _box1.setFillColor(sf::Color(0, 0, 0, 200));
    _box1.setPosition(720 / 2, 480 / 2 - 120);
    _box1.setOrigin(_box1.getGlobalBounds().width / 2, _box1.getGlobalBounds().height / 2);
    _box2.setSize(sf::Vector2f(500, 50));
    _box2.setFillColor(sf::Color(0, 0, 0, 200));
    _box2.setPosition(720 / 2, 480 / 2 + 30);
    _box2.setOrigin(_box2.getGlobalBounds().width / 2, _box2.getGlobalBounds().height / 2);

    _textureButton.loadFromFile("GUI/sprites/button.png");
    _button.setTexture(_textureButton);
    _button.setTextureRect(sf::IntRect(0, 0, 24, 16));
    _button.setPosition(720 / 2, 480 / 2 + 150);
    _button.setOrigin(_button.getGlobalBounds().width / 2, _button.getGlobalBounds().height / 2);
    _button.setScale(5, 5);

    _textButton.setFont(_font);
    _textButton.setString("OK");
    _textButton.setCharacterSize(50);
    _textButton.setFillColor(sf::Color::Black);
    _textButton.setPosition(720 / 2, 480 / 2 + 120);
    _textButton.setOrigin(_textButton.getGlobalBounds().width / 2, _textButton.getGlobalBounds().height / 2);


    _textureBackground.loadFromFile("GUI/sprites/background.png");
    _background.setTexture(_textureBackground);
    _background.setPosition(720 / 2, 480 / 2);
    _background.setTextureRect(sf::IntRect(0, 0, 1903, 1109));
    _background.setScale(0.5, 0.5);
    _background.setOrigin(1903 / 2, 1109 / 2);
    _connected = false;

    _music = new sf::Music();

    _music->openFromFile("GUI/sounds/music/game.ogg");
    _music->setLoop(true);
    _music->play();
}

Menu::~Menu()
{
    _music->stop();
}

void Menu::run()
{
    while (_window->isOpen()) {
        event();
        display();
        _music->setVolume(_musicBar.getVolume());
        if (_connected == true)
            break;
    }
}

void Menu::display()
{
    _window->clear(sf::Color::Blue);
    _window->draw(_background);
    if (_clock.getElapsedTime().asSeconds() > 0.3) {
        _clock.restart();
        if (_background.getTextureRect().left < 1903 * 3)
            _background.setTextureRect(sf::IntRect(_background.getTextureRect().left + 1903, 0, 1903, 1109));
        else
            _background.setTextureRect(sf::IntRect(0, 0, 1903, 1109));
    }
    _window->draw(_box1);
    _window->draw(_box2);
    _window->draw(_text1);
    _window->draw(_text2);
    _window->draw(_textMachine);
    _window->draw(_textPort);
    _window->draw(_button);
    _window->draw(_textButton);
    _musicBar.draw(_window);
    _effectsBar.draw(_window);
    _window->display();
}

void Menu::event()
{
    sf::Event event;
    while (_window->pollEvent(event)) {
        int x = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window)).x;
        int y = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window)).y;
        sf::Vector2f pos = sf::Vector2f((float) x, (float) y);
        if (event.type == sf::Event::Closed)
            _window->close();
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8 && _machine.size() > 0 && _positionWrite == 1) {
                _machine.pop_back();
            } else if (event.text.unicode == 8 && _port.size() > 0 && _positionWrite == 2) {
                _port.pop_back();
            } else if (event.text.unicode > 31 && event.text.unicode < 128 && _machine.size() < 20 && _positionWrite == 1) {
                _machine += static_cast<char>(event.text.unicode);
            } else if (event.text.unicode > 31 && event.text.unicode < 128 && _port.size() < 20 && _positionWrite == 2) {
                _port += static_cast<char>(event.text.unicode);
            } else if (event.text.unicode == 13) {
                try {
                    _portConnect = std::stoi(_port);
                    _connected = true;
                } catch (std::exception &e) {
                }
            }
            _textMachine.setString(_machine);
            _textPort.setString(_port);
            _textMachine.setOrigin(_textMachine.getGlobalBounds().width / 2, _textMachine.getGlobalBounds().height / 2);
            _textPort.setOrigin(_textPort.getGlobalBounds().width / 2, _textPort.getGlobalBounds().height / 2);
        }
        if (_button.getGlobalBounds().contains(pos)) {
            _textButton.setFillColor(sf::Color::White);
            if (event.type == sf::Event::MouseButtonPressed) {
                _button.setTextureRect(sf::IntRect(24, 0, 24, 16));
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                _button.setTextureRect(sf::IntRect(0, 0, 24, 16));
                try {
                    _portConnect = std::stoi(_port);
                    _connected = true;
                } catch (std::exception &e) {
                }
            }
        } else {
            _textButton.setFillColor(sf::Color::Black);
            _button.setTextureRect(sf::IntRect(0, 0, 24, 16));
        }
        if (_box1.getGlobalBounds().contains(pos)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                _positionWrite = 1;
            }
        }
        if (_box2.getGlobalBounds().contains(pos)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                _positionWrite = 2;
            }
        }
        if (_positionWrite == 1) {
            _box1.setFillColor(sf::Color(0, 0, 0, 255));
            _box2.setFillColor(sf::Color(0, 0, 0, 200));
        } else if (_positionWrite == 2) {
            _box1.setFillColor(sf::Color(0, 0, 0, 200));
            _box2.setFillColor(sf::Color(0, 0, 0, 255));
        } else {
            _box1.setFillColor(sf::Color(0, 0, 0, 200));
            _box2.setFillColor(sf::Color(0, 0, 0, 200));
        }
        _effectsBar.event(event, _window);
        _musicBar.event(event, _window);
    }
}


