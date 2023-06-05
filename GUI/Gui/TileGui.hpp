/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** TileGui
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "enum.hpp"
#include "Data.hpp"

class TileGui {
    private:
        sf::Sprite _spriteTile;
        sf::Sprite _spriteRessource;
        sf::IntRect _rect;
        sf::Texture _textureRessource;
        sf::Clock _clock;
        int _frame = 0;
        int _nbFrame = 0;
        int _id = 0;
        Data *_data;
        std::vector<std::vector<sf::Vector2f>> _ressourcesPos;
        int _x = 0;
        int _y = 0;

    public:
        TileGui(int x, int y, int id, sf::Texture *texture, sf::IntRect rect, int rotate, Data *data);
        ~TileGui();
        void update();
        void animate(int timeUnit);
        void display(sf::RenderWindow *window);
        void displayRessources(sf::RenderWindow *window);
        int getId() {return _id;};
};
