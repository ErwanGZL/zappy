#pragma once

#include <iostream>
#include <iomanip>
#include <unistd.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

typedef std::string color_t;

#define _LOG(COLOR, WHAT, MSG) "{" << COLOR << std::to_string(getpid()) << RESET << "} " \
                                   << "[" << COLOR << WHAT << RESET << "] " << MSG << std::endl
#define _LOGERROR(COLOR, WHAT, MSG) "{" << COLOR << std::to_string(getpid()) << RESET << "} " \
                                        << "[" << COLOR << WHAT << RESET << "] " << COLOR << MSG << RESET << std::endl
#define _LOGFILE(WHAT, MSG) "[" << WHAT << "] " << MSG << std::endl

class Logger
{
private:
    std::string _what;
    std::string _file;
    color_t _infocolor = CYAN;
    color_t _warncolor = YELLOW;
    color_t _errcolor = RED;

public:
    enum type_t
    {
        info,
        warning,
        error,
    };
    Logger(std::string what) : _what(what){};
    ~Logger() = default;
    void print(std::string msg, type_t type = info);
    void write(std::string msg, type_t type = info);
    void printAndWrite(std::string msg, type_t type = info)
    {
        print(msg, type);
        write(msg, type);
    };
    Logger setInfoColor(color_t color)
    {
        _infocolor = color;
        return *this;
    };
    Logger setWarnColor(color_t color)
    {
        _warncolor = color;
        return *this;
    };
    Logger setErrColor(color_t color)
    {
        _errcolor = color;
        return *this;
    };
    Logger setFile(std::string file)
    {
        _file = file;
        return *this;
    };
};