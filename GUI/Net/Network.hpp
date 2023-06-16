/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** Network
*/

#pragma once
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <vector>
#include <math.h>

#include "Data.hpp"

void *threadGui(void *arg);

class Network {
    public:
        Network(int ac, char **av);
        ~Network();
        void run();
        std::string getMessage();
        int handleMessages();
        void sendCommand(std::string command);

        int welcome(std::string str);
        int mapSize(std::string str);
        int tileContent(std::string str);
        int teamName(std::string str);
        int playerConnect(std::string str);
        int playerPosition(std::string str);
        int playerLevel(std::string str);
        int playerInventory(std::string str);
        int playerExpulse(std::string str);
        int playerBroadcast(std::string str);
        int startIncantation(std::string str);
        int endIncantation(std::string str);
        int playerLayEgg(std::string str);
        int playerDrop(std::string str);
        int playerTake(std::string str);
        int playerDie(std::string str);
        int eggLay(std::string str);
        int eggConnect(std::string str);
        int eggDie(std::string str);
        int timeUnitRequest(std::string str);
        int timeUnitModification(std::string str);
        int endGame(std::string str);
        int serverMessage(std::string str);
        int unknownCommand(std::string str);
        int commandParameter(std::string str);


    private:
        int _port;
        std::string _machine;
        int _socket;
        struct sockaddr_in _addr;

        Data *_data;

        std::string _buffer;
        pthread_t _guiThread;
        fd_set _readfds;
        struct timeval _tv;
};
