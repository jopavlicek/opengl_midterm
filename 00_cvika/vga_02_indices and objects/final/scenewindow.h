#ifndef SCENEWINDOW_H
#define SCENEWINDOW_H

#include <vector>

#include "openglwindow.h"
#include "rocket.h"
#include "invaderoctopus.h"

class SceneWindow : public OpenGLWindow
{
    std::vector<GraphicalObject*> m_objects;
public:
    SceneWindow();
    ~SceneWindow();

    void initialize();
    void render();
};

#endif // SCENEWINDOW_H
