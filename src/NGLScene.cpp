#include <QMouseEvent>
#include <QGuiApplication>
#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <iostream>

#include <ngl/VAOPrimitives.h>
#include <ngl/VAOFactory.h>
#include <ngl/SimpleIndexVAO.h>
#include <ngl/Transformation.h>
#include <ngl/Random.h>



NGLScene::NGLScene() : m_cam(),m_player()
    {
          setTitle("Space Invaders");
          ngl::Vec2 pos;

          m_animate = false;
          collision = false;
          startGame = false;
          endGame = false;

          for(int j = -6; j <-3;j++)
              {
                  for (int  i= -8; i <10;i+=2)
                      {
                          pos.set(i,j);
                          m_invaderArray.push_back(invader(pos));
                      }
              }
    }

NGLScene::~NGLScene()
    {
      std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
    }

void NGLScene::resizeGL(int _w , int _h)
    {
      m_cam.project = ngl::perspective( 45.0f, static_cast<float>( _w ) / _h, 0.5f, 50.0f );
      m_win.width  = static_cast<int>( _w * devicePixelRatio() );
      m_win.height = static_cast<int>( _h * devicePixelRatio() );
    }

void NGLScene::initializeGL()
    {
         ngl::NGLInit::instance();
         glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
         glEnable(GL_DEPTH_TEST);
         glEnable(GL_MULTISAMPLE);

         m_player.reset( new player(ngl::Vec2(0,11),"models/viper.obj", 10));
         //Viper Obj file https://www.turbosquid.com/FullPreview/Index.cfm/ID/612994//

         m_playerTimer =  startTimer(50);
         m_invaderTimer =  startTimer(2000);

         m_text.reset(new  ngl::Text(QFont("Arial",18)));
         m_text->setScreenSize(width(),height());

         m_text_gameover.reset(new  ngl::Text(QFont("Arial",36)));
         m_text_gameover->setScreenSize(width(),height());
    }

void NGLScene::paintGL()
    {
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         glViewport(0,0,m_win.width,m_win.height);

         m_cam.view=ngl::lookAt(ngl::Vec3(0,30,0),ngl::Vec3(0,0,0),ngl::Vec3(0.0f,0.0f,1.0f));

         m_player->draw(m_cam.project*m_cam.view);

         for(invader i :m_invaderArray)
             {
                 i.draw(m_cam.project*m_cam.view);
             }


         if (m_animate == true)
             {

             if(m_player->m_positionbullet.m_y >-12)
                 {
                     m_player->drawbullet(m_cam.project*m_cam.view);
                 }
             else{m_animate=false;}
             }


         QString text=QString("Score %1").arg(score);

         m_text->setColour(1.0,1.0,1.0);
         m_text_gameover->setColour(1.0,1.0,1.0);
         m_text->renderText(10,18,text);


         if(startGame == false)
            {
                m_text->renderText(120,18*12,"Press Space to Start");
            }
         if(collision == true)
            {
               m_text_gameover->renderText(120,18*12,"GAME OVER!");
            }
         if(endGame == true)
            {
               m_text_gameover->renderText(120,18*12,"YOU WIN!");
            }

    }


void NGLScene::timerEvent(QTimerEvent *_event)
    {
        if(_event->timerId() == m_playerTimer)
            {
               bulletCollision();
            }

        if(_event->timerId() == m_invaderTimer)
            {
                if(collision == false)
                    {
                        if(startGame == true)
                            {
                                for (invader &i :m_invaderArray)
                                    {
                                        i.move();
                                    }
                            }
                    }
                invaderCollision();
            }

        if(m_invaderArray.size() == 0)
            {
                 endGame = true;
            }

        update();
    }

void NGLScene::invaderCollision()
    {
        for(invader i :m_invaderArray)
            {
                if(i.m_position.m_y >= 13)
                    {
                        collision = true;
                    }
                else if(i.collision(m_player->m_position.m_x,m_player->m_position.m_y))
                    {
                        collision = true;
                    }
            }
    }

void NGLScene::bulletCollision()
    {
        if(m_animate == true)
            {
                if(m_player->m_positionbullet.m_y > -10)
                    {
                        for(auto i = m_invaderArray.begin(); i != m_invaderArray.end();)
                            {
                                if(i->collision(m_player->m_positionbullet.m_x,m_player->m_positionbullet.m_y))
                                    {
                                        score += 1;
                                        m_animate = false;
                                        i = m_invaderArray.erase(i);
                                    }
                                else{i++;}
                            }
                    }
                m_player->update();
            }
    }

void NGLScene::keyPressEvent(QKeyEvent *_event)
    {
        int dx=0;

        switch (_event->key())
            {
                case Qt::Key_Escape:
                QGuiApplication::exit(EXIT_SUCCESS);
                break;

                case Qt::Key_Left :if(m_player->m_position.m_x > -10){dx=-1;}; break;
                case Qt::Key_Right :if(m_player->m_position.m_x < 10){dx=+1;}; break;
                case Qt::Key_Space: m_player->setbullet(),  m_animate = true, startGame =true; break;

                default:
                break;
            }

        m_player->move(dx);

        update();
    }


