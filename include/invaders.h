#ifndef INVADERS_H
#define INVADERS_H

#include "Camera.h"
#include <ngl/Vec2.h>
#include <ngl/Obj.h>

class invader
{
    public:

        void draw(const ngl::Mat4 vp_) const;
        void move();
        void set(const ngl::Vec2 &_pos);
        bool collision(float pos_x, float pos_y);

        invader(ngl::Vec2 &_pos);

        ngl::Vec2 m_position={0.0f,-6.0f};

        ~invader() = default;

};

#endif // INVADERS_H
