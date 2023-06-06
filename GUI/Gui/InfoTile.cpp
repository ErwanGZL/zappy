/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** InfoTile
*/

#include "InfoTile.hpp"

InfoTile::InfoTile(Data *data)
{
    _data = data;
    _texture.loadFromFile("GUI/sprites/map.png");
    _sprite.setTexture(_texture);
    _sprite.setScale(1.5, 1.5);
    _font.loadFromFile("GUI/font/monogram.ttf");
    _text.setFont(_font);
    _text.setCharacterSize(30);
    _text.setFillColor(sf::Color::White);
    _text.setString("Tile\nfood\t\nlinemate\t\nderaumere\t\nsibur\t\nmendiane\t\nphiras\t\nthystame\t\n");
    _text.setPosition(0, 0);
    _view.setSize(720, 480);
    _background.setPosition(0, 0);
    _background.setFillColor(sf::Color(0, 0, 0, 200));
    _background.setSize(sf::Vector2f(200, 220));
    _overlay.setSize(sf::Vector2f(16, 16));
    _overlay.setFillColor(sf::Color(0, 0, 0, 200));
    _overlay.setOrigin(8, 8);
}

InfoTile::~InfoTile()
{
}

void InfoTile::update()
{
    std::string str = "Tile\nfood     \t" + std::to_string(_data->getMap()[_x][_y]->getRessources()[0]) +
    "\nlinemate \t" + std::to_string(_data->getMap()[_y][_x]->getRessources()[1]) +
    "\nderaumere\t" + std::to_string(_data->getMap()[_y][_x]->getRessources()[2]) +
    "\nsibur    \t" + std::to_string(_data->getMap()[_y][_x]->getRessources()[3]) +
    "\nmendiane \t" + std::to_string(_data->getMap()[_y][_x]->getRessources()[4]) +
    "\nphiras   \t" + std::to_string(_data->getMap()[_y][_x]->getRessources()[5]) +
    "\nthystame \t" + std::to_string(_data->getMap()[_y][_x]->getRessources()[6]);
    _text.setString(str);
}

void InfoTile::draw(sf::RenderWindow &window)
{
    window.draw(_overlay);
    _view.setCenter(window.getView().getCenter());
    _background.setPosition(window.getView().getCenter().x - 720 / 2, window.getView().getCenter().y - 480 / 2);
    _text.setPosition(window.getView().getCenter().x - 720 / 2 + 30, window.getView().getCenter().y - 480 / 2);
    _sprite.setPosition(window.getView().getCenter().x - 720 / 2, window.getView().getCenter().y - 480 / 2 + 8);
    window.setView(_view);
    if (_isToggled == true) {
        window.draw(_background);
        window.draw(_text);
        for (int i = 0;i < 7;i++) {
            _sprite.setTextureRect(sf::IntRect(16 * i, 16 * 7, 16, 16));
            _sprite.move(0, 24.5);
            window.draw(_sprite);
        }
    }
}

void InfoTile::setMouse(sf::RenderWindow &window, sf::Event event)
{
    int x = window.mapPixelToCoords(sf::Mouse::getPosition(window)).x;
    int y = window.mapPixelToCoords(sf::Mouse::getPosition(window)).y;
    if (x > -8 && x < 152 && y > -8 && y < 152) {
        if (_overlay.getPosition() != sf::Vector2f((x + 8) / 16 * 16, (y + 8) / 16 * 16))
            _isToggled = false;
        _overlay.setPosition(sf::Vector2f((x + 8) / 16 * 16, (y + 8) / 16 * 16));
        if (event.type == sf::Event::MouseButtonReleased) {
            _isToggled = true;
            _x = (x + 8) / 16;
            _y = (y + 8) / 16;
        }
    } else {
        _overlay.setPosition(10000, 10000);
    }
}
