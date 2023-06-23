/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Sound
*/

#include "Sound.hpp"

Sound::Sound(std::string str, int x, int y, int base, int max)
{
    if (base > max)
        base = max;
    _volume = base;
    _max = max;
    _box1.setSize(sf::Vector2f(120, 30));
    _box1.setFillColor(sf::Color(0, 0, 0, 200));
    _box1.setPosition(x, y);
    _box1.setOrigin(_box1.getGlobalBounds().width / 2, _box1.getGlobalBounds().height / 2);
    _box2.setSize(sf::Vector2f(_volume * 100 / max * 1.2, 30));
    _box2.setFillColor(sf::Color(255, 255, 255, 200));
    _box2.setPosition(x - 60, y);
    _box2.setOrigin(0, _box2.getGlobalBounds().height / 2);
    _textureButton.loadFromFile("GUI/sprites/button2.png");
    _buttonPlus.setTexture(_textureButton);
    _buttonPlus.setTextureRect(sf::IntRect(0, 0, 16, 16));
    _buttonPlus.setPosition(x + 100, y);
    _buttonPlus.setOrigin(_buttonPlus.getGlobalBounds().width / 2, _buttonPlus.getGlobalBounds().height / 2);
    _buttonPlus.setScale(3, 3);
    _buttonMinus.setTexture(_textureButton);
    _buttonMinus.setTextureRect(sf::IntRect(0, 0, 16, 16));
    _buttonMinus.setPosition(x - 100, y);
    _buttonMinus.setOrigin(_buttonMinus.getGlobalBounds().width / 2, _buttonMinus.getGlobalBounds().height / 2);
    _buttonMinus.setScale(3, 3);
    _font.loadFromFile("GUI/font/monogram.ttf");
    _text1.setFont(_font);
    _text1.setString(str);
    _text1.setCharacterSize(30);
    _text1.setFillColor(sf::Color::White);
    _text1.setPosition(x, y - 50);
    _text1.setOrigin(_text1.getGlobalBounds().width / 2, _text1.getGlobalBounds().height / 2);
    _text1.setOutlineColor(sf::Color::Black);
    _text1.setOutlineThickness(2);
    _text2.setFont(_font);
    _text2.setString("+");
    _text2.setCharacterSize(50);
    _text2.setFillColor(sf::Color::Black);
    _text2.setPosition(x + 100, y - 35);
    _text2.setOrigin(_text2.getGlobalBounds().width / 2, _text2.getGlobalBounds().height / 2);
    _text3.setFont(_font);
    _text3.setString("-");
    _text3.setCharacterSize(50);
    _text3.setFillColor(sf::Color::Black);
    _text3.setPosition(x - 100, y - 40);
    _text3.setOrigin(_text3.getGlobalBounds().width / 2, _text3.getGlobalBounds().height / 2);
    _view = sf::View(sf::FloatRect(0, 0, 720, 480));
    _x = x;
    _y = y;
}

Sound::~Sound()
{
}

int Sound::getVolume()
{
    return _volume;
}


void Sound::event(sf::Event event, sf::RenderWindow *window)
{
    int x = window->mapPixelToCoords(sf::Mouse::getPosition(*window), _view).x;
    int y = window->mapPixelToCoords(sf::Mouse::getPosition(*window), _view).y;
    sf::Vector2f pos = sf::Vector2f((float) x, (float) y);
    if (_buttonPlus.getGlobalBounds().contains(pos)) {
        _text2.setFillColor(sf::Color::White);
        if (event.type == sf::Event::MouseButtonPressed) {
            _buttonPlus.setTextureRect(sf::IntRect(16, 0, 16, 16));
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            _buttonPlus.setTextureRect(sf::IntRect(0, 0, 16, 16));
            if (_volume != _max)
                _volume += 10 * _max / 100;
        }
    } else {
        _text2.setFillColor(sf::Color::Black);
        _buttonPlus.setTextureRect(sf::IntRect(0, 0, 16, 16));
    }

    if (_buttonMinus.getGlobalBounds().contains(pos)) {
        _text3.setFillColor(sf::Color::White);
        if (event.type == sf::Event::MouseButtonPressed) {
            _buttonMinus.setTextureRect(sf::IntRect(16, 0, 16, 16));
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            _buttonMinus.setTextureRect(sf::IntRect(0, 0, 16, 16));
            if (_volume != 0)
                _volume -= 10 * _max / 100;
        }
    } else {
        _text3.setFillColor(sf::Color::Black);
        _buttonMinus.setTextureRect(sf::IntRect(0, 0, 16, 16));
    }
}

void Sound::draw(sf::RenderWindow *window)
{
    _view.setCenter(window->getView().getCenter());
    setPos(window->getView().getCenter().x - 720 / 2 + _x, window->getView().getCenter().y - 480 / 2 + _y);
    window->setView(_view);
    _box2.setSize(sf::Vector2f(_volume * 100 / _max * 1.2, 30));
    window->draw(_box1);
    window->draw(_box2);
    window->draw(_buttonPlus);
    window->draw(_buttonMinus);
    window->draw(_text1);
    window->draw(_text2);
    window->draw(_text3);
}

void Sound::setPos (int x, int y)
{
    _box1.setPosition(x, y);
    _box2.setPosition(x - 60, y);
    _buttonPlus.setPosition(x + 100, y);
    _buttonMinus.setPosition(x - 100, y);
    _text1.setPosition(x, y - 50);
    _text2.setPosition(x + 100, y - 35);
    _text3.setPosition(x - 100, y - 40);
}