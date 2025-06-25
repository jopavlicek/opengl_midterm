#include "scenewindow.h"

SceneWindow::SceneWindow()
{
}

SceneWindow::~SceneWindow(){
    for (auto object : m_objects) {
        delete object;
    }
}

void SceneWindow::initialize()
{
    m_objects.push_back( new Rocket(Position{0.5, -0.5}) );
    m_objects.push_back( new Rocket(Position{-0.5,-0.5}) );
    m_objects.push_back( new InvaderOctopus(Position{0.5, 0.5}, Color{0.5, 0.5, 0.5}) );

}

void SceneWindow::render()
{
    glClear (GL_COLOR_BUFFER_BIT);

    for (auto object : m_objects) {
        object->render();
    }

    glFlush();

    GLenum err;
    while ((err = m_functions->glGetError()) != GL_NO_ERROR) {
        qDebug() << "OpenGL error: " << err << "\n";
    }
}
