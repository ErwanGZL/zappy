/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Network
*/

#include "Network.hpp"

Network::Network(int ac, char **av)
{
    _port = 4242;
    _machine = "127.0.0.1";
    if ((ac - 1) % 2 != 0) {
        std::cerr << "Invalid number of arguments" << std::endl;
        exit(84);
    }
    for (int i = 1; i < ac; i += 2) {
        if (std::string(av[i]) == "-p") {
            try {
                std::stoi(av[i + 1]);
            } catch (std::exception &e) {
                std::cerr << "Port must be a number" << std::endl;
                exit(84);
            }
            _port = std::stoi(av[i + 1]);
        }
        else if (std::string(av[i]) == "-h")
            _machine = av[i + 1];
        else {
            std::cerr << "Invalid argument" << std::endl;
            exit(84);
        }
    }
    _socket = socket(PF_INET, SOCK_STREAM, 0);
    if (_socket == -1) {
        perror("socket");
        exit(84);
    }
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = inet_addr(_machine.c_str());
    if (::connect(_socket, (struct sockaddr *)&_addr, sizeof(_addr)) == -1) {
        perror("connect");
        exit(84);
    }
    _data = new Data();
}

Network::~Network()
{
}

std::string Network::getMessage()
{
    if (_buffer.find("\n") != std::string::npos) {
        std::string message = _buffer.substr(0, _buffer.find("\n"));
        _buffer = _buffer.substr(_buffer.find("\n") + 1);
        return message;
    }
    char buffer[BUFSIZ] = {0};
    read(_socket, buffer, BUFSIZ);
    _buffer += std::string(buffer);
    std::string message = _buffer.substr(0, _buffer.find("\n"));
    _buffer = _buffer.substr(_buffer.find("\n") + 1);
    return message;
}

void Network::run()
{
    pthread_create(&_guiThread, NULL, threadGui, (void *)_data);
    while (1) {
        if (handleMessages()) return;
    }
}

int Network::handleMessages()
{
    std::string message = getMessage();
    std::string data;
    // std::cout << message << std::endl;
    if (message.find(" ") != std::string::npos)
        data = message.substr(message.find(" ") + 1);

    int returnCode = 0;
    if (message.find("WELCOME") == 0)
        returnCode = welcome(data);
    else if (message.find("msz") == 0)
        returnCode = mapSize(data);
    else if (message.find("bct") == 0)
        returnCode = tileContent(data);
    else if (message.find("tna") == 0)
        returnCode = teamName(data);
    else if (message.find("pnw") == 0)
        returnCode = playerConnect(data);
    else if (message.find("ppo") == 0)
        returnCode = playerPosition(data);
    else if (message.find("plv") == 0)
        returnCode = playerLevel(data);
    else if (message.find("pin") == 0)
        returnCode = playerInventory(data);
    else if (message.find("pex") == 0)
        returnCode = playerExpulse(data);
    else if (message.find("pbc") == 0)
        returnCode = playerBroadcast(data);
    else if (message.find("pic") == 0)
        returnCode = startIncantation(data);
    else if (message.find("pie") == 0)
        returnCode = endIncantation(data);
    else if (message.find("pfk") == 0)
        returnCode = playerLayEgg(data);
    else if (message.find("pdr") == 0)
        returnCode = playerDrop(data);
    else if (message.find("pgt") == 0)
        returnCode = playerTake(data);
    else if (message.find("pdi") == 0)
        returnCode = playerDie(data);
    else if (message.find("enw") == 0)
        returnCode = eggLay(data);
    else if (message.find("eht") == 0)
        returnCode = eggConnect(data);
    else if (message.find("edi") == 0)
        returnCode = eggDie(data);
    else if (message.find("sgt") == 0)
        returnCode = timeUnitRequest(data);
    else if (message.find("sst") == 0)
        returnCode = timeUnitModification(data);
    else if (message.find("seg") == 0)
        returnCode = endGame(data);
    else if (message.find("smg") == 0)
        returnCode = serverMessage(data);
    else if (message.find("suc") == 0)
        returnCode = unknownCommand(data);
    else if (message.find("sbp") == 0)
        returnCode = commandParameter(data);
    else
        std::cout << "Unknown command" << message << std::endl;
    if (returnCode)
        return 1;
    return 0;
}

void Network::sendCommand(std::string command)
{
    command += "\n";
    write(_socket, command.c_str(), command.size());
}
