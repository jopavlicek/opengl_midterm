#include "invader.h"

Invader::Invader(Position position, Color color) : GraphicalObject(position, color) {}

void Invader::render() {
    Vertex octopus[] = {
        { {-0.1f+m_position.x, 0.1f+m_position.y}, {m_color.r, m_color.g, m_color.b} },
        { { 0.1f+m_position.x, 0.1f+m_position.y}, {m_color.r, m_color.g, m_color.b} },
        { {-0.1f+m_position.x,-0.1f+m_position.y}, {m_color.r, m_color.g, m_color.b} },
        { { 0.1f+m_position.x,-0.1f+m_position.y}, {m_color.r, m_color.g, m_color.b} }
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &octopus[0].position);
    glColorPointer(3, GL_FLOAT, sizeof(Vertex), &octopus[0].color);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
