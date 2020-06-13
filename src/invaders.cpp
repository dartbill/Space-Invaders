#include "invaders.h"
#include <ngl/Transformation.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>


invader::invader(ngl::Vec2 &_pos)
    {
        m_position = _pos;
    }

void invader::draw(const ngl::Mat4 vp_) const
    {
      //function to draw the invaders//

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
      shader->setUniform("Colour",1.0f,1.0f,1.0f,1.0f);

      ngl::VAOPrimitives::instance()->draw("troll");

    }

void invader::move( )
    {
        //function to move the invaders in a side then diagonal movement//
        bool down =false;
        if(int(m_position.m_x) % 2 == 0)
            {
                m_position.m_x+=1;
                down =true;

            }
            else
            {
                m_position.m_x-=1;
                down = false;
            }

        if(down)
            {
                 m_position.m_y+=1;
            }
    }

bool invader::collision(float pos_x, float pos_y)
    {
        //function to check whether the invader has the same position as the values inputed//
        if (m_position.m_x == pos_x)
            {
                if(m_position.m_y == pos_y)
                    {
                        return true;
                    }
                    else{return false;}
            }
            else{return false;}
    }

void invader::set(const ngl::Vec2 &_pos)
    {
        m_position=_pos;
    }




