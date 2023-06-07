/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** InfoTeam
*/

#include "InfoTeam.hpp"

InfoTeam::InfoTeam(Data *data, sf::Texture texture, std::string name, int nb)
{
    _data = data;
    _texture = texture;
    _sprite.setTexture(_texture);
    _sprite.setScale(3, 3);
    _sprite.setTextureRect(sf::IntRect(8 * (nb % 5), 0, 8, 8));
    _sprite.setOrigin(8, 0);
    _font.loadFromFile("GUI/font/monogram.ttf");
    _text.setFont(_font);
    _text.setString(name);
    _text.setCharacterSize(30);
    _text.setFillColor(sf::Color::White);
    _text.setPosition(0, 0);
    _background.setFillColor(sf::Color(0, 0, 0, 200));
    _name = name;
    _teamNumber = nb;
    _view.setSize(720, 480);
    _hoover.setSize(sf::Vector2f(8 * 3 + 10, 8 * 3 + 10));
    _hoover.setOrigin(_hoover.getSize().x, 0);
    _hoover.setFillColor(sf::Color(255, 255, 255, 100));
}

InfoTeam::~InfoTeam()
{
}

void InfoTeam::update()
{
    if (_index >= _numberOfPlayers) {
        _index = 0;
        _clicked = false;
    }
    _numberOfPlayers = 0;
    for (int i = 0;i < _data->getPlayers().size();i++) {
        if (_data->getPlayers()[i]->getTeamName() == _name)
            _numberOfPlayers++;
    }
    int width = (_numberOfPlayers * 30 + 10) + 5;
    if (width < _text.getLocalBounds().width + 20)
        width = _text.getLocalBounds().width + 20;
    _background.setSize(sf::Vector2f(width, 8 * 3 + 40));
    _background.setOrigin(_background.getSize().x, 0);
}

void InfoTeam::draw(sf::RenderWindow &window, int display)
{
    _display = display;
    if (display == 1) {
        _view.setCenter(window.getView().getCenter());
        _background.setPosition(window.getView().getCenter().x + 720 / 2 - 10, window.getView().getCenter().y - 480 / 2 + 50 + _teamNumber * (_background.getSize().y + 10));
        _text.setPosition(_background.getPosition().x - _background.getSize().x + 10, _background.getPosition().y - 10);
        window.setView(_view);
        window.draw(_background);
        window.draw(_text);
        if (_clicked) {
            _hoover.setPosition(_background.getPosition().x - 5 - (_index * 30), _background.getPosition().y + 30 - 5);
            window.draw(_hoover);
        }
        for (int i = 0;i < _numberOfPlayers;i++) {
            _sprite.setPosition(_background.getPosition().x - 10 - (i * 30), _background.getPosition().y + 30);
            window.draw(_sprite);
        }
    }
}

bool InfoTeam::setMouse(sf::RenderWindow &window, sf::Event event, sf::View view)
{
    if (event.type == sf::Event::MouseButtonReleased && _display == 1) {
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorld = window.mapPixelToCoords(mouse, _view);
        for (int i = 0;i < _numberOfPlayers;i++) {
            _sprite.setPosition(_background.getPosition().x - 10 - (i * 30), _background.getPosition().y + 30);
            if (_sprite.getGlobalBounds().contains(mouseWorld)) {
                if (i == _index && _clicked) {
                    _clicked = !_clicked;
                } else {
                    _clicked = true;
                }
                _index = i;
                return _clicked;
            }
        }
    }
    return false;
}

sf::View InfoTeam::getView(std::vector<PlayerGui *> player)
{
    int tmp = 0;
    sf::View view;
    for (int i = 0;i < player.size();i++) {
        if (_data->getPlayerById(player[i]->getId()) == NULL)
            continue;
        if (_data->getPlayerById(player[i]->getId())->getTeamName() == _name) {
            if (tmp == _index) {
                view.setCenter(player[i]->getSprite().getPosition());
                view.setSize(720, 480);
                view.zoom(0.2);
                return view;
            }
            tmp++;
        }
    }
    return view;
}
