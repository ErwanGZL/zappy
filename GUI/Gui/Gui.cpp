/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Gui
*/

#include "Gui.hpp"
#include <iostream>
#include <unistd.h>
#include <random>
#include <math.h>

void *threadGui(void *arg)
{
    Gui *gui = new Gui((Data *)arg);
    gui->run();
    return (NULL);
}

Gui::Gui(Data *data)
{
    _data = data;
    _window.create(sf::VideoMode(720, 480), "Zappy");
    _window.setFramerateLimit(60);
    _viewGlobal = _window.getDefaultView();
    _textureMap.loadFromFile("GUI/sprites/map.png");
}

Gui::~Gui()
{
}

void Gui::run ()
{
    generateMap();
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
        _window.clear(sf::Color::Black);
        updateData();
        animate();
        displayMap();
        displayPlayer();
        _window.display();
    }
}

void Gui::generateMap()
{
    int width = _data->getWidth();
    int height = _data->getHeight();
    float ratiox = std::abs(float(_window.getSize().x) / float((width + 4) * 16));
    float ratioy = std::abs(float(_window.getSize().y) / float((height + 4) * 16));
    _viewGlobal.zoom(1./std::min(ratiox, ratioy));
    _viewGlobal.setCenter(width * 8 - 8, height * 8 - 8);
    _window.setView(_viewGlobal);
    Perlin perlin(width, height);
    std::vector<std::vector<int>> noiseMap = perlin.run();
    for (int i = 0; i < noiseMap.size() ; i++) {
        for (int j = 0; j < noiseMap[i].size(); j++) {
            tileData_s *tile = new tileData_s;
            tile->texture = _textureMap;
            tile->rect = getRect(i, j, noiseMap);
            tile->sprite.setTexture(tile->texture);
            tile->sprite.setOrigin(8, 8);
            tile->sprite.setTextureRect(tile->rect);
            tile->sprite.setPosition(j * 16, i * 16);
            tile->nbFrame = (noiseMap[i][j] == 0) ? 3 : 0;
            tile->frame = 0;
            tile->id = noiseMap[i][j];
            _map.push_back(tile);
        }
    }
    for (int i = -width * 2; i < width * 4 ; i++) {
        for (int j =  -height * 2; j < height * 4; j++) {
            if (i < 0 || j < 0 || i >= width || j >= height) {
                tileData_s *tile = new tileData_s;
                int rotate = 0;
                tile->texture = _textureMap;
                tile->rect = getRectBorder(i, j, &rotate);
                tile->sprite.setTexture(tile->texture);
                tile->sprite.setTextureRect(tile->rect);
                tile->sprite.setOrigin(8, 8);
                tile->sprite.setPosition(i * 16, j * 16);
                tile->sprite.setRotation(rotate);
                tile->nbFrame = (tile->rect.top == 16 * 6) ? 3 : 0;
                tile->frame = 0;
                _map.push_back(tile);
            }
        }
    }
}

sf::IntRect Gui::getRectBorder(int x, int y, int *rotate)
{
    int width = _data->getWidth();
    int height = _data->getHeight();
    if (x == -1 && y == -1) {
        *rotate = 0;
        return (sf::IntRect(16 * 2, 16, 16, 16));
    }
    if (x == -1 && y == height) {
        *rotate = 270;
        return (sf::IntRect(16 * 2, 16, 16, 16));
    }
    if (x == width && y == -1) {
        *rotate = 90;
        return (sf::IntRect(16 * 2, 16, 16, 16));
    }
    if (x == width && y == height) {
        *rotate = 180;
        return (sf::IntRect(16 * 2, 16, 16, 16));
    }
    if (x == -1 && y > -1 && y < height) {
        *rotate = 90;
        int random = rand() % 2;
        return (sf::IntRect(16 * random, 16, 16, 16));
    }
    if (x == width && y > -1 && y < height) {
        *rotate = 270;
        int random = rand() % 2;
        return (sf::IntRect(16 * random, 16, 16, 16));
    }
    if (y == -1 && x > -1 && x < width) {
        *rotate = 180;
        int random = rand() % 2;
        return (sf::IntRect(16 * random, 16, 16, 16));
    }
    if (y == height && x > -1 && x < width) {
        *rotate = 0;
        int random = rand() % 2;
        return (sf::IntRect(16 * random, 16, 16, 16));
    }
    *rotate = 0;
    return (sf::IntRect(0, 16 * 6, 16, 16));
}

sf::IntRect Gui::getRect(int x, int y, std::vector<std::vector<int>> mappa)
{
    sf::Vector2i pos;
    int id = mappa[x][y];
    std::vector<int> border = {
        WEST | NORTH,
        NORTH,
        NORTH | EAST,
        WEST | NORTH | EAST,
        WEST | NORTH | SOUTH_EAST,
        NORTH | EAST | SOUTH_WEST,
        WEST,
        EAST,
        WEST | EAST,
        WEST | SOUTH | NORTH_EAST,
        EAST | SOUTH | NORTH_WEST,
        WEST | SOUTH,
        SOUTH,
        SOUTH | EAST,
        WEST | SOUTH | EAST,
        SOUTH_EAST,
        SOUTH_WEST,
        WEST | NORTH | SOUTH,
        NORTH | SOUTH,
        NORTH | SOUTH | EAST,
        WEST | NORTH | SOUTH | EAST,
        NORTH_EAST,
        NORTH_WEST
    };
    if (id == 0) {
        int random = rand() % 2;
        if (random == 0)
            pos = sf::Vector2i(0, 0);
        else
            pos = sf::Vector2i(0, 16 * 5);
    } else if (id == 1) {
        int iy = 16 * 4;
        int orient = 0;
        if (x > 0 && mappa[x - 1][y] != id) {
            orient |= NORTH;
        }
        if (x < mappa.size() - 1 && mappa[x + 1][y] != id)
            orient |= SOUTH;
        if (y > 0 && mappa[x][y - 1] != id)
            orient |= WEST;
        if (y < mappa[x].size() - 1 && mappa[x][y + 1] != id)
            orient |= EAST;
        for (int i = 0; i < border.size(); i++) {
            if (orient == border[i]) {
                pos = sf::Vector2i(16 * i, iy);
                break;
            }
        }
        if (orient == 0) {
            int random = rand() % 14;
            iy = 16 * 2;
            pos = sf::Vector2i(16 * random, iy);
        }
    } else if (id == 2) {
        int x = 16 * (rand() % 10);
        int y = 16 * 3;
        pos = sf::Vector2i(x, y);
    }
    return (sf::IntRect(pos.x, pos.y, 16, 16));
}


void Gui::animate()
{
    for (int i = 0; i < _map.size(); i++) {
        if (_map[i]->nbFrame > 0) {
            if (_map[i]->clock.getElapsedTime().asMilliseconds() > 1000 / _data->getTimeUnit()) {
                _map[i]->frame++;
                if (_map[i]->frame >= _map[i]->nbFrame)
                    _map[i]->frame = 0;
                _map[i]->rect.left = _map[i]->frame * 16;
                _map[i]->sprite.setTextureRect(_map[i]->rect);
                _map[i]->clock.restart();
            }
        }
    }
}

void Gui::displayMap()
{
    for (int i = 0; i < _map.size(); i++) {
        _window.draw(_map[i]->sprite);
    }
}


void Gui::generatePlayer()
{
    std::vector<int> ids;
    for (size_t j = 0;j < _data->getPlayers().size();j++) {
        size_t i = 0;
        for (; i < _players.size(); i++) {
            if (_players[i]->id == _data->getPlayers()[j]->getId())
                break;
        }
        if (i == _players.size())
            ids.push_back(_data->getPlayers()[j]->getId());
    }

    for (size_t i = 0;i < ids.size();i++) {
        int teamId = 0;
        for (; teamId < _data->getTeams().size(); teamId++) {
            if (_data->getTeams()[teamId]->getName() == _data->getPlayerById(ids[i])->getTeamName())
                break;
        }
        teamId %= 5;
        playerSprite_s *player = new playerSprite_s;
        player->stockLeft = teamId * 8 * 16;
        player->sprite.setPosition(sf::Vector2f(_data->getPlayerById(ids[i])->getX() * 16, _data->getPlayerById(ids[i])->getY() * 16));
        int top = (_map[(player->sprite.getPosition().y / 16) * _data->getWidth() + (player->sprite.getPosition().x / 16)]->id == 0) ? 16 * 15 : 16 * 10;
        player->texture.loadFromFile("GUI/sprites/Sprites.png");
        player->rect = sf::IntRect(player->stockLeft, top, 16, 16);
        player->sprite.setTexture(player->texture);
        player->sprite.setTextureRect(player->rect);
        player->sprite.setOrigin(8, 8);
        player->nbFrame = 2;
        player->frame = 0;
        player->id = ids[i];
        _players.push_back(player);
    }

    for (size_t i = 0;i < _players.size();i++) {
        bool found = false;
        for (size_t j = 0;j < _data->getPlayers().size();j++) {
            if (_players[i]->id == _data->getPlayers()[j]->getId())
                found = true;
        }
        if (!found) {
            _players.erase(_players.begin() + i);
            i--;
        }
    }
}

void Gui::updateData()
{
    generatePlayer();
    for (size_t i = 0;i < _players.size();i++) {
        if (_data->getPlayerById(_players[i]->id)->getX() != _players[i]->sprite.getPosition().x / 16 || _data->getPlayerById(_players[i]->id)->getY() != _players[i]->sprite.getPosition().y / 16) {
            _players[i]->isMoving = true;
        } else {
            _players[i]->isMoving = false;
        }
        int elapsedTime = _players[i]->clock.getElapsedTime().asMilliseconds();
        int speed = _data->getTimeUnit() / 10;

        if (elapsedTime > 1000 / _data->getTimeUnit()) {
            Orientation orientation = _data->getPlayerById(_players[i]->id)->getOrientation();
            if (!_players[i]->isMoving) break;

            int top = (_map[(_players[i]->sprite.getPosition().y / 16) * _data->getWidth() + (_players[i]->sprite.getPosition().x / 16)]->id == 0) ? 16 * 15 : 16 * 10;
            _players[i]->rect.top = top;
            if (orientation == NORTH) {
                _players[i]->rect.left = _players[i]->stockLeft + 16 * 2;
                _players[i]->sprite.move(0, -speed);
                if (_players[i]->sprite.getPosition().y < _data->getPlayerById(_players[i]->id)->getY() * 16)
                    _players[i]->sprite.setPosition(_data->getPlayerById(_players[i]->id)->getX() * 16, _data->getPlayerById(_players[i]->id)->getY() * 16);
            } else if (orientation == SOUTH) {
                _players[i]->rect.left = _players[i]->stockLeft + 0;
                _players[i]->sprite.move(0, speed);
                if (_players[i]->sprite.getPosition().y > _data->getPlayerById(_players[i]->id)->getY() * 16)
                    _players[i]->sprite.setPosition(_data->getPlayerById(_players[i]->id)->getX() * 16, _data->getPlayerById(_players[i]->id)->getY() * 16);
            } else if (orientation == EAST) {
                _players[i]->rect.left = _players[i]->stockLeft + 16 * 4;
                _players[i]->sprite.move(speed, 0);
                if (_players[i]->sprite.getPosition().x > _data->getPlayerById(_players[i]->id)->getX() * 16)
                    _players[i]->sprite.setPosition(_data->getPlayerById(_players[i]->id)->getX() * 16, _data->getPlayerById(_players[i]->id)->getY() * 16);
            } else if (orientation == WEST) {
                _players[i]->rect.left = _players[i]->stockLeft + 16 * 6;
                _players[i]->sprite.move(-speed, 0);
                if (_players[i]->sprite.getPosition().x < _data->getPlayerById(_players[i]->id)->getX() * 16)
                    _players[i]->sprite.setPosition(_data->getPlayerById(_players[i]->id)->getX() * 16, _data->getPlayerById(_players[i]->id)->getY() * 16);
            }
            _players[i]->sprite.setTextureRect(_players[i]->rect);
            _players[i]->clock.restart();
        }
    }
}

void Gui::displayPlayer()
{
    for (size_t i = 0;i < _players.size();i++) {
        _window.draw(_players[i]->sprite);
    }
}