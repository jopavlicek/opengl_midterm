#include "graphicalobject.h"

GraphicalObject::GraphicalObject(ShaderProgram* program, VertexBuffer* buffer) {
    m_shaderProgram = program;
    m_vertexBuffer = buffer;
}

GraphicalObject::~GraphicalObject(){
    // nemazat buffer ani program, maji ho i jini
}

void GraphicalObject::addDrawMethod(DrawMethod* drawMethod) {
    m_drawMethods.push_back(drawMethod);
}

void GraphicalObject::render() {
    QOpenGLShaderProgram* program = m_shaderProgram->getProgram();
    GLuint posAttr = m_shaderProgram->getPositionAttr();
    GLuint colAttr = m_shaderProgram->getColorAttr();

    program->bind();
    program->enableAttributeArray(posAttr);
    program->enableAttributeArray(colAttr);

    m_vertexBuffer->bind(); // do not forget!

    program->setAttributeBuffer(posAttr, GL_FLOAT, 0, 2, sizeof(Vertex));
    program->setAttributeBuffer(colAttr, GL_FLOAT, 2*sizeof(GL_FLOAT), 3, sizeof(Vertex));

    // pro každý objekt jiný postup vykreslení
    for (DrawMethod* drawMethod : m_drawMethods) {
        drawMethod->draw();
    }

    program->disableAttributeArray(posAttr);
    program->disableAttributeArray(colAttr);
    program->release();
}
