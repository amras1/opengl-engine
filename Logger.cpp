#include "Logger.h"

void Logger::log(unsigned char where, const std::string &msg) const
{
    if (where & LOG_FILE)
    {
        fwrite(msg.c_str(), msg.size(), 1, file);
        fflush(file);
    }

    if (where & LOG_USER) //TODO: implement pop-up box or similar for log() 7
    {
        std::cerr << msg;
    }
}
