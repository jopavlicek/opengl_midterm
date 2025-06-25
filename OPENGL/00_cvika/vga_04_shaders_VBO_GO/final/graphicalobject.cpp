#include "graphicalobject.h"

GraphicalObject::GraphicalObject(ShaderProgram* program, VertexBuffer* buffer){
    m_program = program;
    m_buffer = buffer;
}

GraphicalObject::~GraphicalObject(){
    // nemazat buffer ani program, maji ho i jini
}

void GraphicalObject::render() const{
    QOpenGLShaderProgram* program = m_program->getProgram();
    GLuint posAttr = m_program->getPositionAttr();
    GLuint colAttr = m_program->getColorAttr();

    program->bind();
    program->enableAttributeArray(posAttr);
    program->enableAttributeArray(colAttr);

    m_buffer->bind(); // do not forget!

    program->setAttributeBuffer(posAttr, GL_FLOAT, 0, 2, sizeof(Vertex));
    program->setAttributeBuffer(colAttr, GL_FLOAT, 2*sizeof(GL_FLOAT), 3, sizeof(Vertex));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    program->disableAttributeArray(posAttr);
    program->disableAttributeArray(colAttr);
    program->release();
}
