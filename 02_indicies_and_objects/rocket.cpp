#include "rocket.h"

Rocket::Rocket(Position position) : GraphicalObject(position, Color{1.0, 0.0, 0.0}) {

}

void Rocket::render() {
    GLfloat rocket[] = {
        // x, y, r, g, b
        // vykreslit verticies do středové souřadnice
        // přičíst position.x/y => objekt se přesune
        0.0f+m_position.x, 0.1f+m_position.y,  m_color.r, m_color.g, m_color.b,
        0.1f+m_position.x,-0.1f+m_position.y,  m_color.r, m_color.g, m_color.b,
        -0.1f+m_position.x,-0.1f+m_position.y,  m_color.r, m_color.g, m_color.b,
        0.0f+m_position.x, 0.05f+m_position.y, 1.0, 1.0, 1.0,
        0.05f+m_position.x,-0.1f+m_position.y, 1.0, 1.0, 1.0,
        -0.05f+m_position.x,-0.1f+m_position.y, 1.0, 1.0, 1.0
    };

    // k vykreslování budu používat vertex array a color array
    // očekávej, že ti do nich něco pošlu
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // pole vertexů očekáven na následující adrese, funguje následovně
    // pole je proložené 2 souřadnice, 3 barvy, 2 souřadnice, 3 barvy...
    // stride: velikost definice jednoho vrcholu – 5 GlFloat hodnot
    // odkaz na první prvek &rocket[0]
    glVertexPointer(2, GL_FLOAT, 5*sizeof(GLfloat), &rocket[0]);
    glColorPointer(3, GL_FLOAT, 5*sizeof(GLfloat), &rocket[2]);

    // vykresli raketu metodou triangles
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // dokončil jsem vykreslování, už nic neočekávej
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
