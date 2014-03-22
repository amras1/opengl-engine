#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cstdio>

extern std::string PATH;

inline void set_path(const std::string &path)
{
    PATH = path;
}

inline std::string extension(const std::string &file)
{
    return file.substr(file.find_last_of('.') + 1);
}

inline FILE *file_open(const char *img, const char *mode)
{
    return fopen((PATH + "Data/" + img).c_str(), mode);
}

inline std::string getpath(const std::string &filename)
{
    size_t pos = filename.rfind('/');
    return (pos != std::string::npos ? filename.substr(0, pos + 1) : "");
}

bool strieq(const std::string &str1, const std::string &str2);

#endif
