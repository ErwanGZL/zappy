/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** main
*/

#include <iostream>
#include "Network.hpp"

int main (int ac, char **av)
{
    try {
        Network *net = new Network(ac, av);
        net->run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}