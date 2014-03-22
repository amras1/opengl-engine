#ifndef MATH_H
#define MATH_H
#include <cmath>

const double PI = 3.14159265358979;

inline float dsin(float degrees)
{
    return sin(degrees * PI / 180.0);
}

inline float dasin(float degrees)
{
    return asin(degrees) * 180.0 / PI;
}

inline float dcos(float degrees)
{
    return cos(degrees * PI / 180.0);
}

inline float dacos(float degrees)
{
    return acos(degrees) * 180.0 / PI;
}

#endif
