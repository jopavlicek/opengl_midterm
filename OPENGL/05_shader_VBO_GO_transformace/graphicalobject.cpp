#include "graphicalobject.h"

GraphicalObject::GraphicalObject(ShaderProgram* program, VertexBuffer* buffer,
                                 Position position, Rotation rotation, Scale scale) {
    m_program = program;
    m_buffer = buffer;
    m_position = position;
    m_rotation = rotation;
    m_scale = scale;
}

GraphicalObject::~GraphicalObject(){
    // nemazat buffer ani program, maji ho i jini
}

void GraphicalObject::addDrawMethod(DrawMethod* drawMethod) {
    m_drawMethods.push_back(drawMethod);
}

void GraphicalObject::render(QMatrix4x4 matrix) {
    QOpenGLShaderProgram* program = m_program->getProgram();
    GLuint posAttr = m_program->getPositionAttr();
    GLuint colAttr = m_program->getColorAttr();
    GLuint matrixId = m_program->getMatrix();

    program->bind();
    program->enableAttributeArray(posAttr);
    program->enableAttributeArray(colAttr);

    m_buffer->bind(); // do not forget!
    program->setUniformValue(matrixId, matrix);
    program->setAttributeBuffer(posAttr, GL_FLOAT, 0, 3, sizeof(Vertex));
    program->setAttributeBuffer(colAttr, GL_FLOAT, 3*sizeof(GL_FLOAT), 3, sizeof(Vertex));

    // pro každý objekt jiný postup vykreslení
    for (DrawMethod* drawMethod : m_drawMethods) {
        drawMethod->draw();
    }

    program->disableAttributeArray(posAttr);
    program->disableAttributeArray(colAttr);
    program->release();
}

Position GraphicalObject::getPosition() {
    return m_position;
}

Rotation GraphicalObject::getRotation() {
    return m_rotation;
}

Scale GraphicalObject::getScale() {
    return m_scale;
}
