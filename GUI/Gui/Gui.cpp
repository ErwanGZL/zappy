/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Gui
*/

#include "Gui.hpp"

void *threadGui(void *arg)
{
    Gui *gui = new Gui((Data *)arg);
    gui->run();
    return (NULL);
}

Gui::Gui(Data *data)
{
    _data = data;
    // _window.create(sf::VideoMode(1920, 1080), "Zappy");
    // _window.setFramerateLimit(60);
    // _view = _window.getDefaultView();
}

Gui::~Gui()
{
}

void Gui::run ()
{
}