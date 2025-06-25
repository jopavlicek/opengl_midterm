#include "drawmethod.h"
#include <QOpenGLFunctions>

DrawMethod::DrawMethod(int mode, int first, int count) {
    m_mode = mode;
    m_first = first;
    m_count = count;
}

void DrawMethod::draw() {
    glDrawArrays(m_mode, m_first, m_count);
}
