/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Gui
*/

#include "Gui.hpp"
#include "Menu.hpp"
#include <iostream>
#include <unistd.h>
#include <random>
#include <math.h>

void *threadGui(void *arg)
{
    Data *data = (Data *)arg;
    Menu *menu = new Menu();
    if (data->getMachine() == "" || data->getPort() == -1) {
        menu->run();
        data->setMachine(menu->getMachine());
        data->setPort(menu->getPort());
    }
    data->post();
    usleep(100000);
    data->wait();
    Gui *gui = new Gui(data, menu->getWindow(), menu->getMusicVolume(), menu->getEffectVolume(), menu->getMusic());
    gui->run();
    delete gui;
    delete menu;
    return (NULL);
}

Gui::Gui(Data *data, sf::RenderWindow *window, int vol1, int vol2, sf::Music *music) : _musicBar("Music", 720 / 2 - 230, 480 / 2 + 200, vol1), _effectBar("Effects", 720 / 2 + 230, 480 / 2 + 200, vol2)
{
    _data = data;
    _window = window;
    _viewGlobal = _window->getDefaultView();
    _textureMap.loadFromFile("GUI/sprites/map.png");
    _texturePlayer.loadFromFile("GUI/sprites/Sprites.png");
    _infoTile = new InfoTile(_data);
    _infoPlayer = new InfoPlayer(_data);
    _egg = new EggGui(_data, &_texturePlayer);
    _music = music;
}

Gui::~Gui()
{
    for (int i = 0; i < _map.size(); i++) {
        delete _map[i];
    }
    for (int i = 0; i < _players.size(); i++) {
        delete _players[i];
    }
    delete _egg;
    delete _infoTile;
    delete _infoPlayer;
}

void Gui::run ()
{
    bool generated = false;
    while (_window->isOpen()) {
        _music->setVolume(_musicBar.getVolume());
        if (_data->stop == true) {
            _window->close();
            return;
        }
        if (_data->getWidth() != -1 && _data->getHeight() != -1 && generated == false) {
            generateMap();
            generated = true;
        }
        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _data->stop = true;
                return;
            }
            if (generated == true) {
                _infoTile->setMouse(*_window, event);
                _infoPlayer->setMouse(*_window, event, _viewGlobal);
            }
            _musicBar.event(event, _window);
            _effectBar.event(event, _window);
        }
        if (generated == true) {
            _window->clear(sf::Color::Black);
            updateData();
            animate();
            display();
        }
        _window->display();
    }
}

void Gui::generateMap()
{
    int width = _data->getWidth();
    int height = _data->getHeight();
    float ratiox = std::abs(float(_window->getSize().x) / float((width + 4) * 16));
    float ratioy = std::abs(float(_window->getSize().y) / float((height + 4) * 16));
    _viewGlobal.zoom(1./std::min(ratiox, ratioy));
    _viewGlobal.setCenter(width * 8 - 8, height * 8 - 8);
    _window->setView(_viewGlobal);
    _currentView = _viewGlobal;
    Perlin perlin(width, height);
    std::vector<std::vector<int>> noiseMap = perlin.run();
    for (int i = 0; i < noiseMap.size() ; i++) {
        for (int j = 0; j < noiseMap[i].size(); j++) {
            TileGui *tile = new TileGui(j * 16, i * 16, noiseMap[i][j], &_textureMap, getRect(i, j, noiseMap), 0, _data);
            _map.push_back(tile);
        }
    }
    for (int i = -width * 2 - 1; i < width * 4 ; i++) {
        for (int j =  -height * 2 - 1; j < height * 4; j++) {
            if (i < 0 || j < 0 || i >= width || j >= height) {
                int rotate = 0;
                sf::IntRect rect = getRectBorder(i, j, &rotate);
                TileGui *tile = new TileGui(i * 16, j * 16, -1, &_textureMap, rect, rotate, _data);
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
    if (_data->getTimeUnit() == 0)
        return;
    for (int i = 0; i < _map.size(); i++) {
        _map[i]->animate(_data->getTimeUnit());
    }
    for (int i = 0;i < _players.size();i++) {
        _players[i]->animate(_data->getTimeUnit());
    }
}

void Gui::display()
{
    _window->setView(_currentView);
    for (int i = 0; i < _map.size(); i++) {
        _map[i]->display(_window);
    }
    _window->setView(_currentView);
    for (int i = 0; i < _map.size(); i++) {
        _map[i]->displayRessources(_window);
    }
    _window->setView(_currentView);
    _egg->draw(_window);
    _window->setView(_currentView);
    for (size_t i = 0;i < _players.size();i++) {
        _players[i]->draw(_window);
    }
    _window->setView(_currentView);
    _infoTile->draw(*_window);
    _window->setView(_currentView);
    _infoPlayer->draw(*_window);
    _musicBar.draw(_window);
    _effectBar.draw(_window);
    _window->setView(_currentView);
}

void Gui::generatePlayer()
{
    std::vector<int> ids;
    for (size_t j = 0;j < _data->getPlayers().size();j++) {
        size_t i = 0;
        for (; i < _players.size(); i++) {
            if (_players[i]->getId() == _data->getPlayers()[j]->getId())
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
        PlayerGui *player = new PlayerGui(ids[i], &_texturePlayer, teamId, _data);
        _players.push_back(player);
    }

    for (size_t i = 0;i < _players.size();i++) {
        bool found = false;
        for (size_t j = 0;j < _data->getPlayers().size();j++) {
            if (_players[i]->getId() == _data->getPlayers()[j]->getId())
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
    _currentView = _infoPlayer->getView(_viewGlobal, _players);
    generatePlayer();
    for (size_t i = 0;i < _players.size();i++) {
        _players[i]->update(_map[_players[i]->getX() / 16 + _players[i]->getY() / 16 * _data->getWidth()]->getId(), _effectBar.getVolume());
    }
    for (size_t i = 0;i < _map.size();i++) {
        _map[i]->update();
    }
    _infoTile->update();
    _infoPlayer->update();
}