#include "player.h"
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/VAOFactory.h>

#include <ngl/Random.h>
#include <ngl/NGLStream.h>
#include <ngl/SimpleVAO.h>

player::player(ngl::Vec2 _pos, std::string _fname, size_t _numBullets)
    {
      //create VAO for loading in obj//
        m_position=_pos;
        m_mesh.reset( new ngl::Obj(_fname));
        m_mesh->createVAO();
        m_vao=ngl::VAOFactory::createVAO(ngl::simpleVAO,GL_POINTS);

        //set num of bullets, used for future expansion of having more bullets on screen//
        m_bullets.resize(_numBullets);

        m_vao=ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_POINTS);
    }

void player::draw(const ngl::Mat4 vp_) const
    {
      //function for drawing the player//
      ngl::ShaderLib *shader=ngl::ShaderLib::instance();
      shader->use(ngl::nglColourShader);
      ngl::Mat4 MVP;

      float halfY=0.5f;
      float halfX=0.5f;

      ngl::Transformation tx;
      tx.setRotation(0,static_cast<float>(0),0);
      tx.setPosition(halfX-m_position.m_x,0.5f,halfY-m_position.m_y);
      MVP = vp_ * tx.getMatrix();

      shader->setUniform("MVP",MVP);
      shader->setUniform("Colour",0.0f,1.0f,0.0f,1.0f);

      m_mesh->draw();
    }

void player::move( float _x)
    {
        m_position.m_x+=_x;
    }

void player::setbullet()
    {
     m_positionbullet.m_x = m_position.m_x;
     m_positionbullet.m_y = m_position.m_y;
    }

void player::update()
    {
        m_positionbullet.m_y-=1;
    }

void player::drawbullet(const ngl::Mat4 vp_) const
    {
        //function for drawing bullet//
        ngl::ShaderLib *shader=ngl::ShaderLib::instance();
        shader->use(ngl::nglColourShader);

        ngl::Mat4 MVP;
        ngl::Transformation tx;
        tx.setRotation(0,static_cast<float>(0),0);
        tx.setPosition(0.5f-m_positionbullet.m_x,0.5f,0.5f-m_positionbullet.m_y);
        MVP = vp_ * tx.getMatrix();
        shader->setUniform("MVP",MVP);
        shader->setUniform("Colour",0.0f,1.0f,0.0f,0.0f);

        glPointSize(10);

        m_vao->bind();
        m_vao->setData(ngl::SimpleVAO::VertexData(m_bullets.size()*sizeof(Bullet),
                                                  m_bullets[0].pos.m_x));
        m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Bullet),0);
        m_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(Bullet),3);
        m_vao->setNumIndices(m_bullets.size());
        m_vao->draw();
        m_vao->unbind();

    }
