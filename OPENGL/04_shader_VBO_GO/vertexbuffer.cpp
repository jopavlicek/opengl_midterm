#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(Vertex verticies[], GLuint verticiesCount) {
    m_buffer = new QOpenGLBuffer();
    m_buffer->create();
    m_buffer->setUsagePattern(QOpenGLBuffer::StreamDraw);
    m_buffer->bind();
    m_buffer->allocate(verticies, verticiesCount*sizeof(Vertex));
}

void VertexBuffer::bind() {
    m_buffer->bind();
}

VertexBuffer::~VertexBuffer() {
    delete m_buffer;
}
