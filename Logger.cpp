#include "Logger.h"
#include <ctime>

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

Logger::Logger()
{
    file = file_open(LOG_FILE_NAME, "a+");
    log(LOG_FILE, "Beginning program...\nStart time: ");
    std::time_t now = std::time(0);
    char str[60];
    std::time_t time;
    std::time(&time);
    std::strftime(str, 60, "%H:%M:%S on %m/%d/%Y", std::localtime(&time));
    logln(LOG_FILE, str);
}

Logger::~Logger()
{
    log(LOG_FILE, "End time: ");
    std::time_t now = std::time(0);
    char str[60];
    std::time_t time;
    std::time(&time);
    std::strftime(str, 60, "%H:%M:%S on %m/%d/%Y", std::localtime(&time));
    logln(LOG_FILE, str);
    logln(LOG_FILE, "Program quit\n");
    fclose(file);
}
