#include "scenewindow.h"

#define GL_SILENCE_DEPRECATION

SceneWindow::SceneWindow() { }

SceneWindow::~SceneWindow() { }

void SceneWindow::initialize()
{

}

void SceneWindow::render()
{

    // (2) DOMEČEK
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat houseVerticies[] = {
        // čtverec
        -0.2,  0.0,
        -0.2, -0.4,
         0.2,  0.0,
         0.2, -0.4,
        // střecha
        -0.3, 0.0,
         0.3, 0.0,
         0.0, 0.2,
        // slunce
         0.5, 0.5, // 7
         0.5, 0.8, // 8
         0.6, 0.6,
         0.8, 0.5,
         0.6, 0.4,
         0.5, 0.2,
         0.4, 0.4,
         0.2, 0.5,
         0.4, 0.6,
         // 0.5, 0.8  // odkaz na 8
    };

    GLfloat houseColors[] = {
        // čtverec
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        // střecha
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        // slunce
        1.0, 0.6, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0
    };

    GLubyte sunIndicies[] {
        7, 8, 9, 10, 11, 12, 13, 14, 15, 8
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, houseVerticies);
    glColorPointer(3, GL_FLOAT, 0, houseColors);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 4, 3);

    // 1) Možnost vykreslit slunce přes triangle fan normálně
    // glDrawArrays(GL_TRIANGLE_FAN, 7, 10);

    // 2) Možnost použít indicies k vykreslení – není nutné duplikovat body
    glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_BYTE, sunIndicies);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glFlush();


    // (1) ZÁKLADNÍ TROJŮHELNÍK RGB
    // glClear(GL_COLOR_BUFFER_BIT);

    // GLfloat verticies[] = {
    //     -0.5, 0.5,  // x1, y1
    //      0.5, 0.5,  // x2, y2
    //     -0.5,-0.5,  // x3, y3
    // };

    // GLfloat colors[] = {
    //      1.0, 0.0, 0.0,  // r1, g1, b1
    //      0.0, 0.0, 1.0,  // r2, g2, b2
    //      0.0, 1.0, 0.0   // r3, g3, b3
    // };

    // glEnableClientState(GL_VERTEX_ARRAY);
    // glEnableClientState(GL_COLOR_ARRAY);

    // glVertexPointer(2, GL_FLOAT, 0, verticies);
    // glColorPointer(3, GL_FLOAT, 0, colors);

    // glDrawArrays(GL_TRIANGLES, 0, 3);

    // glDisableClientState(GL_VERTEX_ARRAY);
    // glDisableClientState(GL_COLOR_ARRAY);
    // glFlush();

    GLenum err;
    while ((err = m_functions->glGetError()) != GL_NO_ERROR) {
        qDebug() << "OpenGL error: " << err << "\n";
    }
}
