#ifndef SCENEWINDOW_H
#define SCENEWINDOW_H

#include <vector>

#include "openglwindow.h"
#include "graphicalobject.h"

class SceneWindow : public OpenGLWindow
{
private:
    std::vector<GraphicalObject*> m_objects;
public:
    SceneWindow();
    ~SceneWindow();

    void initialize();
    void render();
};

#endif // SCENEWINDOW_H
