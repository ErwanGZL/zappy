/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** EggGui
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "enum.hpp"
#include "Data.hpp"

class EggGui {
    public:
        EggGui(Data *data, sf::Texture *texture);
        ~EggGui();
        void update();
        void draw(sf::RenderWindow *window);

    private:
        Data *_data;
        sf::Sprite _sprite;
        sf::Texture *_texture;
        sf::IntRect _rect;
};

