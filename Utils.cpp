#include "Utils.h"

std::string PATH;

bool strieq(const std::string &str1, const std::string &str2)
{
    unsigned int len = str1.length();

    if (len != str2.length())
        return false;

    for (unsigned int i = 0; i < len; ++i)
        if (toupper(str1[i]) != toupper(str2[i]))
            return false;
    return true;
}
