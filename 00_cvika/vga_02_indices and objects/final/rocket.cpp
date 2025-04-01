#include "rocket.h"

Rocket::Rocket(Position position): GraphicalObject(position, Color{1.0, 0.0, 0.0}) {

}

void Rocket::render() {
    GLfloat rocket[] = {
         0.0f+m_position.x, 0.1f+m_position.y,  m_color.r, m_color.g, m_color.b,
         0.1f+m_position.x,-0.1f+m_position.y,  m_color.r, m_color.g, m_color.b,
        -0.1f+m_position.x,-0.1f+m_position.y,  m_color.r, m_color.g, m_color.b,
         0.0f+m_position.x, 0.05f+m_position.y, 1.0, 1.0, 1.0,
         0.05f+m_position.x,-0.1f+m_position.y, 1.0, 1.0, 1.0,
        -0.05f+m_position.x,-0.1f+m_position.y, 1.0, 1.0, 1.0
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2, GL_FLOAT, 5*sizeof(GLfloat), &rocket[0]);
    glColorPointer(3, GL_FLOAT, 5*sizeof(GLfloat), &rocket[2]);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
