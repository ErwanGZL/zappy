#include "Logger.hpp"
#include <fstream>

void Logger::print(std::string msg, type_t type)
{
    switch (type)
    {
    case info:
        std::cout << _LOG(_infocolor, _what, msg);
        break;
    case warning:
        std::cout << _LOG(_warncolor, _what, msg);
        break;
    case error:
        std::cout << _LOGERROR(_errcolor, _what, msg);
        break;
    }
}

void Logger::write(std::string msg, type_t type)
{
    std::ofstream ofs;
    if (_file == "")
        ofs = std::ofstream(_what + ".log", std::ios_base::app);
    else
        ofs = std::ofstream(_file, std::ios_base::app);

    switch (type)
    {
    case info:
        ofs << "---[INFO] " << _LOGFILE(_what, msg);
        break;
    case warning:
        ofs << "[WARNING] " << _LOGFILE(_what, msg);
        break;
    case error:
        ofs << "--[ERROR] " <<_LOGFILE(_what, msg);
        break;
    }
    ofs.close();
}