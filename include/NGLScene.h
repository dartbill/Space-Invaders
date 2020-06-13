#ifndef NGLSCENE_H_
#define NGLSCENE_H_
#include "WindowParams.h"
#include <ngl/Text.h>
//#include <ngl/Vec3.h>
#include <QOpenGLWindow>
#include "player.h"

#include <QKeyEvent>



//----------------------------------------------------------------------------------------------------------------------
/// @file NGLScene.h
/// @brief this class inherits from the Qt OpenGLWindow and allows us to use NGL to draw OpenGL
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/9/13
/// Revision History :
/// This is an initial version used for the new NGL6 / Qt 5 demos
/// @class NGLScene
/// @brief our main glwindow widget for NGL applications all drawing elements are
/// put in this file
//----------------------------------------------------------------------------------------------------------------------

class NGLScene : public QOpenGLWindow
{
  public:

       NGLScene();
       ~NGLScene() override;
        void initializeGL() override;
        void paintGL() override;
        void resizeGL(int _w, int _h) override;
        void invaderCollision();
        void bulletCollision() ;

  private:

        void keyPressEvent(QKeyEvent *_event) override;

        void timerEvent(QTimerEvent *_event) override;

        WinParams m_win;
        ngl::Vec3 m_modelPos;

        Camera m_cam;

        std::unique_ptr<player> m_player;
        std::vector <invader> m_invaderArray;
        std::unique_ptr<ngl::Text> m_text;
        std::unique_ptr<ngl::Text> m_text_gameover;

        bool m_animate;
        bool collision;
        bool startGame;
        bool endGame;

        int score = 0;
        int m_playerTimer;
        int m_invaderTimer;

};



#endif
