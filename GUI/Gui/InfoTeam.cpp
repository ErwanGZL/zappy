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
    _texturePlayer.loadFromFile("GUI/sprites/map.png");
    _texture = texture;
    _sprite.setTexture(_texture);
    _sprite.setScale(3, 3);
    _sprite.setTextureRect(sf::IntRect(8 * (nb % 5), 0, 8, 8));
    _sprite.setOrigin(8, 0);
    _spritePlayer.setTexture(_texturePlayer);
    _spritePlayer.setScale(1.5, 1.5);
    _font.loadFromFile("GUI/font/monogram.ttf");
    _text.setFont(_font);
    _text.setCharacterSize(30);
    _text.setFillColor(sf::Color::White);
    _text.setString(name);
    _textPlayer.setFont(_font);
    _textPlayer.setCharacterSize(30);
    _textPlayer.setFillColor(sf::Color::White);
    _textPlayer2.setFont(_font);
    _textPlayer2.setCharacterSize(30);
    _textPlayer2.setFillColor(sf::Color::White);
    _textPlayer2.setOutlineThickness(1);
    _textPlayer2.setOutlineColor(sf::Color::Black);
    _textPlayer3.setFont(_font);
    _textPlayer3.setCharacterSize(30);
    _textPlayer3.setFillColor(sf::Color::White);
    _background.setFillColor(sf::Color(0, 0, 0, 200));
    _backgroundPlayer.setFillColor(sf::Color(0, 0, 0, 200));
    _backgroundPlayer.setSize(sf::Vector2f(200, 200));
    _backgroundPlayer.setOrigin(100, 100);
    _backgroundText.setFillColor(sf::Color(0, 0, 0, 200));
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
    std::vector<int> ressources = {0, 0, 0, 0, 0, 0, 0};
    int level = 0;
    if (_index >= _numberOfPlayers) {
        _clicked = false;
        _index = -1;
    }
    _numberOfPlayers = 0;
    _broadcast = 0;
    for (int i = 0;i < _data->getPlayers().size();i++) {
        if (_data->getPlayers()[i]->getTeamName() == _name) {
            _numberOfPlayers++;
            if (i == _index && _clicked) {
                ressources = _data->getPlayers()[i]->getRessources();
                level = _data->getPlayers()[i]->getLevel();
                _textPlayer3.setString(_data->getPlayers()[i]->getMessage());
                _broadcast = (_data->getPlayers()[i]->getStatus() == BROADCASTING) ? 1 : 0;
            }
        }
    }
    int width = (_numberOfPlayers * 30 + 10) + 5;
    if (width < _text.getLocalBounds().width + 20)
        width = _text.getLocalBounds().width + 20;
    _background.setSize(sf::Vector2f(width, 8 * 3 + 40));
    _background.setOrigin(_background.getSize().x, 0);

    std::string str =
    "   Food:      " + std::to_string(ressources[0]) +
    "\n   Linemate:  " + std::to_string(ressources[1]) +
    "\n   Deraumere: " + std::to_string(ressources[2]) +
    "\n   Sibur:     " + std::to_string(ressources[3]) +
    "\n   Mendiane:  " + std::to_string(ressources[4]) +
    "\n   Phiras:    " + std::to_string(ressources[5]) +
    "\n   Thystame:  " + std::to_string(ressources[6]);
    _textPlayer.setString(str);
    _textPlayer.setOrigin(_textPlayer.getLocalBounds().width / 2, _textPlayer.getLocalBounds().height / 2);

    str = "LEVEL: " + std::to_string(level);
    _textPlayer2.setString(str);
    _textPlayer2.setOrigin(_textPlayer2.getLocalBounds().width / 2, _textPlayer2.getLocalBounds().height / 2);
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

            _backgroundPlayer.setPosition(window.getView().getCenter().x, window.getView().getCenter().y + 140);
            _textPlayer.setPosition(_backgroundPlayer.getPosition().x, _backgroundPlayer.getPosition().y);
            _textPlayer2.setPosition(_backgroundPlayer.getPosition().x, _backgroundPlayer.getPosition().y - 100);
            window.draw(_backgroundPlayer);
            window.draw(_textPlayer);
            window.draw(_textPlayer2);
            if (_broadcast == 1) {
                _textPlayer3.setOrigin(_textPlayer3.getLocalBounds().width / 2, _textPlayer3.getLocalBounds().height / 2);
                _textPlayer3.setPosition(_backgroundPlayer.getPosition().x, _backgroundPlayer.getPosition().y - 300);
                _backgroundText.setSize(sf::Vector2f(_textPlayer3.getLocalBounds().width + 20, _textPlayer3.getLocalBounds().height + 20));
                _backgroundText.setOrigin(_backgroundText.getSize().x / 2, _backgroundText.getSize().y / 2);
                _backgroundText.setPosition(_backgroundPlayer.getPosition().x, _backgroundPlayer.getPosition().y - 280);
                window.draw(_backgroundText);
                window.draw(_textPlayer3);
            }
            for (int i = 0;i < 7; i++) {
                _spritePlayer.setPosition(_backgroundPlayer.getPosition().x - 85, _backgroundPlayer.getPosition().y - 75 + (i * 25));
                _spritePlayer.setTextureRect(sf::IntRect(16 * i, 16 * 7, 16, 16));
                window.draw(_spritePlayer);
            }
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
                    _clicked = false;
                    _index = -1;
                } else {
                    _clicked = true;
                    _index = i;
                }
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
