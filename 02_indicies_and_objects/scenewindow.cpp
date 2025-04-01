#include "scenewindow.h"
#include "rocket.h"
#include "invader.h"

SceneWindow::SceneWindow() {}

SceneWindow::~SceneWindow()
{
    // vymaž všechny objekty kvůli memory leaks
    for (auto object : m_objects) {
        delete object;
    }
}

void SceneWindow::initialize()
{
    Rocket* r1 = new Rocket(Position{0.5, -0.5});
    Rocket* r2 = new Rocket(Position{-0.5, -0.5});
    Invader* i1 = new Invader(Position{0.5, 0.5}, Color{0.5, 0.5, 0.5});

    m_objects.push_back(r1);
    m_objects.push_back(r2);
    m_objects.push_back(i1);
}

void SceneWindow::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // vykresli všechny objekty z vektoru objektů m_objects
    for (auto object : m_objects) {
        object->render();
    }

    glFlush();

    GLenum err;
    while ((err = m_functions->glGetError()) != GL_NO_ERROR) {
        qDebug() << "OpenGL error: " << err << "\n";
    }
}
