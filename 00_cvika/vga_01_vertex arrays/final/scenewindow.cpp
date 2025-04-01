#include "scenewindow.h"

SceneWindow::SceneWindow()
{
}

SceneWindow::~SceneWindow(){
}

void SceneWindow::initialize()
{

}

void SceneWindow::render()
{
    glClear (GL_COLOR_BUFFER_BIT);

    GLfloat coords[] = {
        -0.5,-0.5,  // 0
         0.5,-0.5,  // 1
        -0.5,-1.0,  // 2
         0.5,-1.0,  // 3
         0.0, 0.0,
         0.5,-0.5,
        -0.5,-0.5,

        0.00, 0.5,  // 7
        0.25, 0.75, // 8
        0.25, 0.25,
        0.50, 0.0,
        0.75, 0.25,
        1.00, 0.5,
        0.75, 0.75,
        0.50, 1.0
    };

    GLubyte indices[] = {7,8,9,9,10,11,11,12,13,13,14,8};

    GLfloat colors[] = {
         1.0, 1.0, 0.0,  // r1, g1, b1
         1.0, 1.0, 0.0,  // r2, g2, b2
         1.0, 1.0, 0.0,  // r3, g3, b3
         1.0, 1.0, 0.0,  // r1, g1, b1
         1.0, 0.0, 0.0,
         1.0, 0.0, 0.0,
         1.0, 0.0, 0.0,

        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, coords);
    glColorPointer(3, GL_FLOAT, 0, colors);

    //glVertexPointer(2, GL_FLOAT, 5*sizeof(GL_FLOAT), &data[0]);
    //glColorPointer(3, GL_FLOAT, 5*sizeof(GL_FLOAT), &data[2]);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDrawArrays(GL_TRIANGLES, 4, 3);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices);


    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glFlush();

    GLenum err;
    while ((err = m_functions->glGetError()) != GL_NO_ERROR) {
        qDebug() << "OpenGL error: " << err << "\n";
    }
}
