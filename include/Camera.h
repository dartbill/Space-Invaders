#ifndef CAMERA_H
#define CAMERA_H
#include <ngl/Mat4.h>


struct Camera
{
    ngl::Mat4 view;
    ngl::Mat4 project;
};

#endif // CAMERA_H
