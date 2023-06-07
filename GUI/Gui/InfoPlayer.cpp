/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** InfoPlayer
*/

#include "InfoPlayer.hpp"

InfoPlayer::InfoPlayer(Data *data)
{
    _data = data;
    _button.setSize(sf::Vector2f(32, 32));
    _button.setFillColor(sf::Color::Black);
    _button.setOrigin(_button.getSize().x, 0);
    _texture.loadFromFile("GUI/sprites/icons.png");
    _view.setSize(720, 480);
    for (int i = 0;i < _data->getTeams().size();i++) {
        _teams.push_back(new InfoTeam(_data, _texture, _data->getTeams()[i]->getName(), i));
    }
}

InfoPlayer::~InfoPlayer()
{
}

void InfoPlayer::setMouse(sf::RenderWindow &window, sf::Event event, sf::View view)
{
    for (int i = 0;i < _teams.size();i++) {
        _teams[i]->setMouse(window, event, view);
    }
}

void InfoPlayer::update()
{
    for (int i = 0;i < _teams.size();i++) {
        _teams[i]->update();
    }
}

void InfoPlayer::draw(sf::RenderWindow &window)
{
    _view.setCenter(window.getView().getCenter());
    _button.setPosition(window.getView().getCenter().x + 720 / 2 - 10, window.getView().getCenter().y - 480 / 2 + 10);
    sf::View view = window.getView();
    for (int i = 0;i < _teams.size();i++) {
        window.setView(view);
        _teams[i]->draw(window, 1);
    }
    window.setView(_view);
    window.draw(_button);
}

