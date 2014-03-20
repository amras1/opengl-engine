#include "Camera.h"
#include "Vector.h"
#include "Vector.cpp" //TODO: something weird with linkage, needs to be fixed 3
#include <GL/glu.h>
#include "Math.h"

void Camera::orient(bool translate) const
{
    glLoadIdentity();
    Point3f eye = position + forward;
    gluLookAt(position.getX(), position.getY(), position.getZ(), eye.getX(), eye.getY(), eye.getZ(), up.getX(), up.getY(), up.getZ());

    if (!translate)
    {
        float mat[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, mat);
        mat[12] = 0.0;
        mat[13] = 0.0;
        mat[14] = 0.0;
        glLoadMatrixf(mat);
    }
}

void Camera::rotateX(GLfloat rot)
{
    up = dcos(rot) * up + dcos(rot + 90.0) * forward;
    up.normalize();
    forward = dcos(90.0 - rot) * up + dcos(rot) * forward;
    forward.normalize();
}

void Camera::rotateY(GLfloat rot) // counter-clockwise
{
    right = dcos(rot) * right + dcos(rot + 90.0) * forward;
    right.normalize();
    forward = dcos(90.0 - rot) * right + dcos(rot) * forward;
    forward.normalize();
}

void Camera::rotateZ(GLfloat rot)
{
    right = dcos(rot) * right + dcos(rot + 90.0) * up;
    right.normalize();
    up = dcos(90.0 - rot) * right + dcos(rot) * up;
    up.normalize();
}

void Camera::lookAt(const Point3f &p) //TODO: check to see if this works 8
{
    forward = p - position;
    forward.normalize();
    Vector3f projection = forward;
    projection.setY(0.0);
    projection.normalize();
    Vector3f y_axis(0.0, 1.0, 0.0);
    right = -projection.cross(y_axis);
    right.normalize();
    up = forward.cross(right);
    up.normalize();
}
