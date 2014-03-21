#include "Vector.h"
#include "Debug.h"
#include <iostream>
#include <cmath>

template <class T>
T Vector3<T>::dot(const Vector3<T> &v) const
{
    return (x * v.getX() + y * v.getY() + z * v.getZ());
}

template <class T>
T Vector3<T>::length() const
{
    return sqrt(x * x + y * y + z * z);
}

template <class T>
Vector3<T> Vector3<T>::normal() const
{
    T len = length();
    ASSERT(len > 0);
    return Vector3<T>(x / len, y / len, z / len);
}
