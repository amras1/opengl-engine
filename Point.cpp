#include "Point.h"

template <class T>
std::ostream &operator<<(std::ostream &stream, const Point3<T> &p)
{
    return (stream << "(" << p.x << ", " << p.y << ", " << p.z << ")");
}
