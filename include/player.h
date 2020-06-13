#ifndef SNAKE_H
#define SNAKE_H

#include "invaders.h"
#include <ngl/ShaderLib.h>
#include <ngl/Obj.h>
#include "bullet.h"
#include <ngl/AbstractVAO.h>


class player
{
    public:

        void draw(const ngl::Mat4 vp_) const;
        void move(float _x);
        void update();
        void setbullet();
        void drawbullet(const ngl::Mat4 vp_) const;

        ngl::Vec2 m_position={0.0f,11.0f};
        ngl::Vec2 m_positionbullet={0.0f,0.0f};
        std::vector<Bullet> m_bullets;

        player(ngl::Vec2 _pos, std::string _fname, size_t _numBullets);

        ~player() = default;

    private :

        std::unique_ptr<ngl::Obj>m_mesh;
        std::unique_ptr<ngl::AbstractVAO> m_vao;

};


#endif // SNAKE_H
