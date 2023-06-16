/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Gui
*/

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include "Data.hpp"
#include "Perlin.hpp"
#include "TileGui.hpp"
#include "PlayerGui.hpp"
#include "EggGui.hpp"
#include "InfoTile.hpp"
#include "InfoPlayer.hpp"
#include <climits>
#include <cstdlib>
#include "Sound.hpp"

class Gui {
    public:
        Gui(Data *data, sf::RenderWindow *window, int vol1, int vol2, sf::Music *music);
        ~Gui();
        void run();
        void generateMap();
        void generatePlayer();
        void updateData();
        void display();
        void animate();

    private:
        int _port;
        std::string _machine;
        sf::RenderWindow *_window;
        sf::View _viewGlobal;
        sf::View _currentView;
        sf::Font _font;

        sf::Texture _textureMap;
        sf::Texture _texturePlayer;

        std::vector<TileGui*> _map;
        std::vector<PlayerGui*> _players;
        EggGui *_egg;
        InfoTile *_infoTile;
        InfoPlayer *_infoPlayer;
        sf::IntRect getRect(int x, int y, std::vector<std::vector<int>> map);
        sf::IntRect getRectBorder(int x, int y, int *rotate);

        Data *_data;
        Sound _musicBar;
        Sound _effectBar;
        sf::Music *_music;

        sf::Sprite *_tile;
};
