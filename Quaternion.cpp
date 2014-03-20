#include "Quaternion.h"

void Quaternion::set(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

void Quaternion::setXYZ(const Vector3f &vec)
{
    x = vec.getX();
    y = vec.getY();
    z = vec.getZ();
}

Quaternion Quaternion::operator*(const Quaternion &quat) const
{
    return Quaternion(w * quat.x + x * quat.w + y * quat.z - z * quat.y,
                      w * quat.y - x * quat.z + y * quat.w + z * quat.x,
                      w * quat.z + x * quat.y - y * quat.x + z * quat.w,
                      w * quat.w - x * quat.x - y * quat.y - z * quat.z);
}
