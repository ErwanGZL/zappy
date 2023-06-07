/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** PlayerGui
*/

#include "PlayerGui.hpp"

PlayerGui::PlayerGui(int id, sf::Texture *texture, int teamId, Data *data)
{
    _data = data;
    _texture = texture;
    _teamId = teamId;
    _id = id;
    _nextX = _data->getPlayerById(id)->getX() * 16;
    _nextY = _data->getPlayerById(id)->getY() * 16;
    // _stockLeft = teamId * 8 * 16;
    _sprite.setTexture(*_texture);
    _sprite.setPosition(_nextX, _nextY);
    _sprite.setTextureRect(_rect);
    _sprite.setOrigin(8, 8);
    _nbFrame = 2;
    _frame = 0;
    _rect = sf::IntRect(0, 0, 16, 16);
    _rect = sf::IntRect(_teamId * 8 * 16, stateTop(), 16, 16);
}

PlayerGui::~PlayerGui()
{
}

int PlayerGui::stateTop()
{
    int top = 0;
    Player *player = _data->getPlayerById(_id);
    PlayerStatus status = player->getStatus();
    if (status == NONE)
        top = (_tileId == 0) ? 16 * 15 : 16 * 10;
    else if (status == INCANTATION)
        top = 16 * 14;
    else if (status == PUSHING)
        top = 16 * 12;
    else if (status == LAYING)
        top = 16 * 13;
    return (top);
}

void PlayerGui::update(int tileId)
{
    _tileId = tileId;
    _nextX = _data->getPlayerById(_id)->getX() * 16;
    _nextY = _data->getPlayerById(_id)->getY() * 16;
    if (_data->getPlayerById(_id)->getX() != _sprite.getPosition().x / 16 || _data->getPlayerById(_id)->getY() != _sprite.getPosition().y / 16) {
            _isMoving = true;
    } else {
        _isMoving = false;
    }
    int elapsedTime = _clock.getElapsedTime().asMilliseconds();
    float speed = _data->getTimeUnit() / 10.;

    if (elapsedTime > 10) {
        Orientation orientation = _data->getPlayerById(_id)->getOrientation();

        int top = stateTop();
        _rect.top = top;
        if (_isMoving) {
            if (orientation == NORTH) {
                _rect.left = (_teamId * 8 * 16) + 16 * 2;
                _left = (_teamId * 8 * 16) + 16 * 2;
                _sprite.move(0, -speed);
                if (_sprite.getPosition().y < _nextY)
                    _sprite.setPosition(_nextX, _nextY);
            } else if (orientation == SOUTH) {
                _rect.left = (_teamId * 8 * 16) + 0;
                _left = (_teamId * 8 * 16) + 0;
                _sprite.move(0, speed);
                if (_sprite.getPosition().y > _nextY)
                    _sprite.setPosition(_nextX, _nextY);
            } else if (orientation == EAST) {
                _rect.left = (_teamId * 8 * 16) + 16 * 4;
                _left = (_teamId * 8 * 16) + 16 * 4;
                _sprite.move(speed, 0);
                if (_sprite.getPosition().x > _nextX)
                    _sprite.setPosition(_nextX, _nextY);
            } else if (orientation == WEST) {
                _rect.left = (_teamId * 8 * 16) + 16 * 6;
                _left = (_teamId * 8 * 16) + 16 * 6;
                _sprite.move(-speed, 0);
                if (_sprite.getPosition().x < _nextX)
                    _sprite.setPosition(_nextX, _nextY);
            }
        }
        _rect.left = _left + (_frame * 16);
        _sprite.setTextureRect(_rect);
        _clock.restart();
    }
}

void PlayerGui::animate(int timeUnit)
{
    if (_nbFrame > 0) {
        if (_clockAnimate.getElapsedTime().asMilliseconds() > 1000 / _data->getTimeUnit() && _isMoving) {
            _rect.left = _left + (_frame * 16);
            _sprite.setTextureRect(_rect);
            _clockAnimate.restart();
            _frame++;
            if (_frame >= _nbFrame)
                _frame = 0;
        }
    }
}

