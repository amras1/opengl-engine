#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector.h"
#include "Point.h"
#include "Debug.h"
#include <cmath>

class Quaternion
{
    friend inline std::ostream &operator<<(std::ostream &stream, const Quaternion &q)
    {
        return (stream << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")");
    }
private:
    float x, y, z, w;
public:
    Quaternion(float _x = 0.0, float _y = 0.0, float _z = 0.0, float _w = 0.0) : x(_x), y(_y), z(_z), w(_w)
    {
    }

    Quaternion(const Quaternion &quat) : x(quat.x), y(quat.y), z(quat.z), w(quat.w)
    {
    }

    Quaternion(float theta, Vector3f axis) : w(cos(theta / 2.0))
    {
        setXYZ(axis * sin(theta / 2.0));
    }

    void set(const Quaternion &quat)
    {
        set(quat.x, quat.y, quat.z, quat.w);
    }

    void set(float, float, float, float);
    void setXYZ(const Vector3f &);

    Vector3f getXYZ() const
    {
        return Vector3f(x, y, z);
    }

    Quaternion &operator=(const Quaternion &quat)
    {
        set(quat);
        return *this;
    }

    bool operator==(const Quaternion &quat)
    {
        return (x == quat.x && y == quat.y && z == quat.z && w == quat.w);
    }

    bool operator!=(const Quaternion &quat)
    {
        return !(*this == quat);
    }

    float getX() const
    {
        return x;
    }

    void setX(float _x)
    {
        x = _x;
    }

    float getY() const
    {
        return y;
    }

    void setY(float _y)
    {
        y = _y;
    }

    float getZ() const
    {
        return z;
    }

    void setZ(float _z)
    {
        z = _z;
    }

    float getW() const
    {
        return w;
    }

    void setW(float _w)
    {
        w = _w;
    }

    Quaternion operator+(const Quaternion &quat) const
    {
        return Quaternion(x + quat.x, y + quat.y, z + quat.z, w + quat.w);
    }

    Quaternion &operator+=(const Quaternion &quat)
    {
        return (*this = *this + quat);
    }

    Quaternion operator-(const Quaternion &quat) const
    {
        return *this + (-quat);
    }

    Quaternion &operator-=(const Quaternion &quat)
    {
        return (*this = *this - quat);
    }

    Quaternion operator-() const
    {
        return Quaternion(-x, -y, -z, -w);
    }

    Quaternion conjugate() const
    {
        return Quaternion(-x, -y, -z, w);
    }

    operator Vector3f() const
    {
        return Vector3f(x, y, z);
    }

    operator Point3f() const
    {
        return Point3f(x, y, z);
    }

    Point3f rotate(const Vector3f &v) //TODO: fix rotate() 4
    {
        normalize();
        return (*this * v.normal() * conjugate());
    }

    Quaternion operator*(const Quaternion &) const;

    Quaternion &operator*=(const Quaternion &quat)
    {
        return (*this = *this + quat);
    }

    float magnitude() const
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    Quaternion normal() const
    {
        float mag = magnitude();
        ASSERT(mag > 0);
        return Quaternion(x / mag, y / mag, z / mag, w / mag);
    }

    void normalize()
    {
        *this = normal();
    }
};

inline Point3f rotate(const Point3f &p, float theta, const Vector3f &axis)
{
    return Quaternion(theta, axis).rotate(p);
}

template <class T>
inline Point3<T>::operator Quaternion() const
{
    return Quaternion(x, y, z, 0.0);
}

template <class T>
inline Vector3<T>::operator Quaternion() const
{
    return Quaternion(x, y, z, 0.0);
}

#endif
