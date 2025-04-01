#ifndef SCENEWINDOW_H
#define SCENEWINDOW_H

#include "openglwindow.h"

class SceneWindow : public OpenGLWindow
{
public:
    SceneWindow();
    ~SceneWindow();

    void initialize();
    void render();
};

#endif // SCENEWINDOW_H
