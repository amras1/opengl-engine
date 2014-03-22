#ifndef CAMERA_H
#define CAMERA_H
#include "GLIncludes.h"
#include "Vector.h"
#include "Point.h"
#include "Point.cpp" //TODO: fix this 3

class Camera
{
private:
    Point3f position;
    Vector3f up, forward, right;
public:
    Camera(const Point3f &p = Point3f(0.0, 0.0, 0.0)) : position(p), up(0.0, 1.0, 0.0), forward(0.0, 0.0, -1.0), right(1.0, 0.0, 0.0) { }

    void orient(bool translate = true) const;

    void orientBefore() const
    {
        orient(false);
    }

    void rotateX(GLfloat x);
    void rotateY(GLfloat y);
    void rotateZ(GLfloat z);

    void advance(GLfloat scalar)
    {
        position += forward * scalar;
    }

    void moveTo(const Point3f &pos)
    {
        position = pos;
    }

    void movePos(const Vector3f &vec)
    {
        position += vec;
    }

    void move(const Vector3f &vec)
    {
        position += (vec.getX() * right + vec.getY() * up + vec.getZ() * forward);
    }

    void lookAt(const Point3f &);

    Point3f getPos() const
    {
        return position;
    }

    Vector3f getUp() const
    {
        return up;
    }

    void setUp(const Vector3f &_up)
    {
        up = _up;
    }

    Vector3f getForward() const
    {
        return forward;
    }

    void setForward(const Vector3f &_forward)
    {
        forward = _forward;
    }

    Vector3f getRight() const
    {
        return right;
    }

    void setRight(const Vector3f &_right)
    {
        right = _right;
    }

    bool operator==(const Camera &cam) const
    {
        return (position == cam.position && up == cam.up && forward == cam.forward && right == cam.right);
    }

    bool operator!=(const Camera &cam) const
    {
        return !(*this == cam);
    }
};

#endif
