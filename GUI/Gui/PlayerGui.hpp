/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** PlayerGui
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "enum.hpp"
#include "Data.hpp"

class PlayerGui {
    public:
        PlayerGui(int id, sf::Texture *texture, int teamId, Data *data);
        ~PlayerGui();
        void update(int tileId, int volume);
        void animate(int timeUnit);
        void draw(sf::RenderWindow *window);
        sf::Sprite getSprite() {return _sprite;};
        int getX() {return _nextX;};
        int getY() {return _nextY;};
        int getId() {return _id;};
        int stateTop();

    private:
        sf::Sprite _sprite;
        sf::Sprite _spriteBroadcast;
        sf::Texture *_texture;
        sf::IntRect _rect;
        sf::Clock _clock;
        sf::Clock _clockAnimate;
        bool _isMoving = false;
        int _frame = 0;
        int _nbFrame = 0;
        int _id = 0;
        int _left = 0;
        int _teamId = 0;

        int _nextX = 0;
        int _nextY = 0;
        int _tileId = 1;
        Data *_data;

        sf::SoundBuffer _bufferBroadcast;
        sf::Sound _soundBroadcast;
        sf::SoundBuffer _bufferIncantation;
        sf::Sound _soundIncantation;
        sf::SoundBuffer _bufferEgg;
        sf::Sound _soundEgg;
        sf::SoundBuffer _bufferWalk;
        sf::Sound _soundWalk;
};
