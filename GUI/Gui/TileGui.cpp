/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** TileGui
*/

#include "TileGui.hpp"

TileGui::TileGui(int x, int y, int id, sf::Texture *texture, sf::IntRect rect, int rotate, Data *data)
{
    _data = data;
    _x = x;
    _y = y;
    _spriteTile.setTexture(*texture);
    _spriteRessource.setTexture(*texture);
    _spriteRessource.setOrigin(8, 8);
    _spriteRessource.setScale(0.5, 0.5);
    _spriteTile.setTextureRect(rect);
    _spriteTile.setPosition(x, y);
    _spriteTile.setOrigin(8, 8);
    _spriteTile.setRotation(rotate);
    _rect = rect;
    _id = id;
    _nbFrame = (rect.top == 16 * 6 || id == 0) ? 3 : 0;
    _frame = 0;
    _ressourcesPos = std::vector<std::vector<sf::Vector2f>>(8);
}

TileGui::~TileGui()
{
}

void TileGui::update()
{
    if (_id == -1) return;
    for (int i = 0; i < 7; i++) {
        int nb = _data->getMap()[_y/16][_x/16]->getRessources()[i];
        if (nb > _ressourcesPos[i].size()) {
            for (int j = 0; j < nb; j++) {
                sf::Vector2f pos = sf::Vector2f(_x + rand() % 16, _y + rand() % 16);
                _ressourcesPos[i].push_back(pos);
            }
        } else if (nb < _ressourcesPos[i].size()) {
            _ressourcesPos[i].erase(_ressourcesPos[i].begin() + nb, _ressourcesPos[i].end());
        }
    }
}

void TileGui::animate(int timeUnit)
{
    if (_nbFrame > 0) {
        if (_clock.getElapsedTime().asMilliseconds() > 1000 / timeUnit) {
            _frame++;
            if (_frame >= _nbFrame)
                _frame = 0;
            _rect.left = _frame * 16;
            _spriteTile.setTextureRect(_rect);
            _clock.restart();
        }
    }
}

void TileGui::display(sf::RenderWindow *window)
{
    window->draw(_spriteTile);
}

void TileGui::displayRessources(sf::RenderWindow *window)
{
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < _ressourcesPos[i].size(); j++) {
            sf::Vector2f pos = _ressourcesPos[i][j];
            sf::IntRect rect = sf::IntRect(i * 16, 7 * 16, 16, 16);
            _spriteRessource.setTextureRect(rect);
            _spriteRessource.setPosition(pos);
            window->draw(_spriteRessource);
        }
    }
}
