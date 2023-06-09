/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Player
*/

#include "Player.hpp"

Player::Player()
{
}

Player::~Player()
{
}

void Player::setRessources(std::vector<int> ressources)
{
    _ressources = ressources;
}

void Player::addLevel()
{
    _level++;
}

void Player::setLevel(int level)
{
    _level = level;
}

void Player::setId(int id)
{
    _id = id;
}

void Player::setX(int x)
{
    _x = x;
}

void Player::setY(int y)
{
    _y = y;
}

void Player::setOrientation(Orientation orientation)
{
    _orientation = orientation;
}

void Player::setTeamName(std::string teamName)
{
    _teamName = teamName;
}

std::vector<int> Player::getRessources()
{
    return _ressources;
}

int Player::getLevel()
{
    return _level;
}

int Player::getId()
{
    return _id;
}

int Player::getX()
{
    return _x;
}

int Player::getY()
{
    return _y;
}

Orientation Player::getOrientation()
{
    return _orientation;
}

std::string Player::getTeamName()
{
    return _teamName;
}

void Player::broadcast(std::string message)
{
    _message = message;
    _status = PlayerStatus::BROADCASTING;
}

void Player::setStatus(PlayerStatus status)
{
    _status = status;
}

PlayerStatus Player::getStatus()
{
    return _status;
}
