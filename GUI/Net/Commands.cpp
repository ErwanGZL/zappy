/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Commands
*/

#include "Network.hpp"

int Network::welcome(std::string str)
{
    sendCommand("GRAPHIC");
    return 0;
}

int Network::mapSize(std::string str)
{
    int x = std::stoi(str.substr(0, str.find(" ")));
    int y = std::stoi(str.substr(str.find(" ") + 1));
    _data->createMap(x, y);
    return 0;
}

int Network::tileContent(std::string str)
{
    std::vector<int> ressources;
    std::string tmp = str;
    int x = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int y = std::stoi(tmp.substr(0, tmp.find(" ")));
    while (tmp.find(" ") != std::string::npos) {
        tmp = tmp.substr(tmp.find(" ") + 1);
        ressources.push_back(std::stoi(tmp.substr(0, tmp.find(" "))));
    }
    _data->setMap(x, y, ressources);
    return 0;
}

int Network::teamName(std::string str)
{
    std::string tmp = str.substr(str.find(" ") + 1);
    _data->addTeam(tmp);
    return 0;
}

int Network::playerConnect(std::string str)
{
    std::string tmp = str;
    int id = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int x = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int y = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int o = std::stoi(tmp.substr(0, tmp.find(" "))) - 1;
    if (o == 0) o = 2;
    else if (o == 2) o = 0;
    Orientation orientation = static_cast<Orientation>(pow(2, o));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int level = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    std::string team = tmp.substr(0, tmp.find(" "));
    _data->addPlayer(id, x, y, orientation, level, team);
    sendCommand("pin " + std::to_string(id));
    sendCommand("plv " + std::to_string(id));
    return 0;
}

int Network::playerPosition(std::string str)
{
    std::string tmp = str;
    int id = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int x = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int y = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int o = std::stoi(tmp.substr(0, tmp.find(" "))) - 1;
    if (o == 0) o = 2;
    else if (o == 2) o = 0;
    Orientation orientation = static_cast<Orientation>(pow(2, o));
    _data->getPlayerById(id)->setX(x);
    _data->getPlayerById(id)->setY(y);
    _data->getPlayerById(id)->setOrientation(orientation);
    _data->getPlayerById(id)->setStatus(NONE);
    return 0;
}

int Network::playerLevel(std::string str)
{
    int id = std::stoi(str.substr(0, str.find(" ")));
    int level = std::stoi(str.substr(str.find(" ") + 1));
    _data->getPlayerById(id)->setLevel(level);
    return 0;
}

int Network::playerInventory(std::string str)
{
    std::vector<int> ressources;
    std::string tmp = str;
    int id = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int x = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int y = std::stoi(tmp.substr(0, tmp.find(" ")));
    while (tmp.find(" ") != std::string::npos) {
        tmp = tmp.substr(tmp.find(" ") + 1);
        ressources.push_back(std::stoi(tmp.substr(0, tmp.find(" "))));
    }
    _data->getPlayerById(id)->setRessources(ressources);
    return 0;
}

int Network::playerExpulse(std::string str)
{
    int index = std::stoi(str.substr(0, str.find(" ")));
    int x = _data->getPlayerById(index)->getX();
    int y = _data->getPlayerById(index)->getY();
    Orientation orientation = _data->getPlayerById(index)->getOrientation();
    if (orientation == NORTH)
        y -= 1;
    else if (orientation == SOUTH)
        y += 1;
    else if (orientation == EAST)
        x += 1;
    else if (orientation == WEST)
        x -= 1;
    std::vector<Player*> players = _data->getPlayersByCoords(x, y);
    for (int i = 0; i < players.size(); i++) {
        if (players[i]->getId() != index) {
            players[i]->setX(x);
            players[i]->setY(y);
        }
    }
    return 0;
}

int Network::playerBroadcast(std::string str)
{
    int index = std::stoi(str.substr(0, str.find(" ")));
    _data->getPlayerById(index)->broadcast(str.substr(str.find(" ") + 1));
    return 0;
}

int Network::startIncantation(std::string str)
{
    std::string tmp = str;
    int x = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int y = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int level = std::stoi(tmp.substr(0, tmp.find(" ")));
    while (tmp.find(" ") != std::string::npos) {
        tmp = tmp.substr(tmp.find(" ") + 1);
        _data->getPlayerById(std::stoi(tmp.substr(0, tmp.find(" "))))->setStatus(INCANTATION);
    }
    return 0;
}

int Network::endIncantation(std::string str)
{
    std::string tmp = str;
    int x = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int y = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    std::vector<Player*> players = _data->getPlayersByCoords(x, y);
    for (int i = 0; i < players.size(); i++) {
        players[i]->setStatus(NONE);
        sendCommand("plv " + std::to_string(players[i]->getId()));
    }
    return 0;
}

int Network::playerLayEgg(std::string str)
{
    int index = std::stoi(str.substr(0, str.find(" ")));
    _data->getPlayerById(index)->setStatus(LAYING);
    return 0;
}

int Network::playerDrop(std::string str)
{
    int index = std::stoi(str.substr(0, str.find(" ")));
    std::vector<int> ressources = _data->getPlayerById(index)->getRessources();
    _data->getPlayerById(index)->setStatus(NONE);
    int ressource = std::stoi(str.substr(str.find(" ") + 1));
    ressources[ressource] -= 1;
    sendCommand("mct");
    return 0;
}

int Network::playerTake(std::string str)
{
    int index = std::stoi(str.substr(0, str.find(" ")));
    std::vector<int> ressources = _data->getPlayerById(index)->getRessources();
    _data->getPlayerById(index)->setStatus(NONE);
    int ressource = std::stoi(str.substr(str.find(" ") + 1));
    ressources[ressource] += 1;
    sendCommand("mct");
    return 0;
}

int Network::playerDie(std::string str)
{
    int index = std::stoi(str.substr(0, str.find(" ")));
    _data->removePlayer(index);
    return 0;
}

int Network::eggLay(std::string str)
{
    std::string tmp = str;
    int e = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int n = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int x = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int y = std::stoi(tmp.substr(0, tmp.find(" ")));
    _data->addEgg(e, x, y, "team");
    return 0;
}

int Network::eggConnect(std::string str)
{
    return 0;
}

int Network::eggDie(std::string str)
{
    int e = std::stoi(str.substr(0, str.find(" ")));
    Egg *egg = _data->getEggById(e);
    delete egg;
    _data->removeEgg(e);
    return 0;
}

int Network::timeUnitRequest(std::string str)
{
    _data->setTimeUnit(std::stoi(str));
    return 0;
}

int Network::timeUnitModification(std::string str)
{
    _data->setTimeUnit(std::stoi(str));
    return 0;
}

int Network::endGame(std::string str)
{
    return 1;
}

int Network::serverMessage(std::string str)
{
    std::string message = str.substr(str.find(" ") + 1);
    std::cout << "Message from server: " << message << std::endl;
    return 0;
}

int Network::unknownCommand(std::string str)
{
    std::cout << "unknown command sent" << std::endl;
    return 0;
}

int Network::commandParameter(std::string str)
{
    std::cout << "command parameter wrong" << std::endl;
    return 0;
}
