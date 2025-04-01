#include "graphicalobject.h"

GraphicalObject::GraphicalObject(ShaderProgram* program, VertexBuffer* buffer,
                                 Position position, Rotation rotation){
    m_program = program;
    m_buffer = buffer;
    m_position = position;
    m_rotation = rotation;
}

GraphicalObject::~GraphicalObject(){
    // nemazat buffer ani program, maji ho i jini
}

void GraphicalObject::render(QMatrix4x4 matrix) const{
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

    glDrawArrays(GL_TRIANGLES, 0, m_buffer->getNumberOfVertices());

    program->disableAttributeArray(posAttr);
    program->disableAttributeArray(colAttr);
    program->release();
}

Position GraphicalObject::getPosition() const{
    return m_position;
}

Rotation GraphicalObject::getRotation() const{
    return m_rotation;
}
