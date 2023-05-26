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
    int x = std::stoi(str.substr(0, str.find(" ")));
    int y = std::stoi(str.substr(str.find(" ") + 1));
    std::string tmp = str.substr(str.find(" ") + 1);
    tmp = tmp.substr(tmp.find(" ") + 1);
    while (tmp.find(" ") != std::string::npos) {
        ressources.push_back(std::stoi(tmp.substr(0, tmp.find(" "))));
        tmp = tmp.substr(tmp.find(" ") + 1);
    }
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
    int id = std::stoi(str.substr(0, str.find(" ")));
    int x = std::stoi(str.substr(str.find(" ") + 1));
    int y = std::stoi(str.substr(str.find(" ") + 1));
    std::string tmp = str.substr(str.find(" ") + 1);
    tmp = tmp.substr(tmp.find(" ") + 1);
    Orientation orientation = static_cast<Orientation>(std::stoi(tmp.substr(0, tmp.find(" "))));
    tmp = tmp.substr(tmp.find(" ") + 1);
    int level = std::stoi(tmp.substr(0, tmp.find(" ")));
    tmp = tmp.substr(tmp.find(" ") + 1);
    std::string team = tmp.substr(0, tmp.find(" "));
    _data->addPlayer(id, x, y, orientation, level, team);
    return 0;
}

int Network::playerPosition(std::string str)
{
    int id = std::stoi(str.substr(0, str.find(" ")));
    int x = std::stoi(str.substr(str.find(" ") + 1));
    int y = std::stoi(str.substr(str.find(" ") + 1));
    _data->getPlayerById(id)->setX(x);
    _data->getPlayerById(id)->setY(y);
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
    int id = std::stoi(str.substr(0, str.find(" ")));
    std::string tmp = str.substr(str.find(" ") + 1);
    while (tmp.find(" ") != std::string::npos) {
        ressources.push_back(std::stoi(tmp.substr(0, tmp.find(" "))));
        tmp = tmp.substr(tmp.find(" ") + 1);
    }
    _data->getPlayerById(id)->setRessources(ressources);
    return 0;
}

int Network::playerExpulse(std::string str)
{
    std::cout << "playerExpulse" << std::endl;
    std::cout << "NOT IMPLEMENTED" << std::endl;
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
    std::cout << "playerStartIncantation" << std::endl;
    std::cout << "NOT IMPLEMENTED" << std::endl;
    return 0;
}

int Network::endIncantation(std::string str)
{
    std::cout << "playerEndIncantation" << std::endl;
    std::cout << "NOT IMPLEMENTED" << std::endl;
    return 0;
}

int Network::playerLayEgg(std::string str)
{
    std::cout << "playerLayEgg" << std::endl;
    std::cout << "NOT IMPLEMENTED" << std::endl;
    return 0;
}

int Network::playerDrop(std::string str)
{
    int index = std::stoi(str.substr(0, str.find(" ")));
    std::vector<int> ressources = _data->getPlayerById(index)->getRessources();
    int ressource = std::stoi(str.substr(str.find(" ") + 1));
    ressources[ressource] -= 1;
    sendCommand("mct");
    return 0;
}

int Network::playerTake(std::string str)
{
    int index = std::stoi(str.substr(0, str.find(" ")));
    std::vector<int> ressources = _data->getPlayerById(index)->getRessources();
    int ressource = std::stoi(str.substr(str.find(" ") + 1));
    ressources[ressource] += 1;
    sendCommand("mct");
    return 0;
}

int Network::playerDie(std::string str)
{
    int index = std::stoi(str.substr(0, str.find(" ")));
    _data->getPlayerById(index)->setStatus(DEAD);
    return 0;
}

int Network::eggLay(std::string str)
{
    std::cout << "eggLay";
    std::cout << "NOT IMPLEMENTED" << std::endl;
    return 0;
}

int Network::eggConnect(std::string str)
{
    std::cout << "eggConnect";
    std::cout << "NOT IMPLEMENTED" << std::endl;
    return 0;
}

int Network::eggDie(std::string str)
{
    std::cout << "eggDie";
    std::cout << "NOT IMPLEMENTED" << std::endl;
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
    std::cout << "unknown command" << std::endl;
    return 0;
}

int Network::commandParameter(std::string str)
{
    std::cout << "command parameter" << std::endl;
    std::cout << "NOT IMPLEMENTED" << std::endl;
    return 0;
}
