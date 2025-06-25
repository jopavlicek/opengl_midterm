#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(const Vertex array[], const GLuint verticesCount){
    m_buffer = new QOpenGLBuffer();
    m_buffer->create();
    m_buffer->setUsagePattern( QOpenGLBuffer::StreamDraw );
    m_buffer->bind();
    m_buffer->allocate( array, verticesCount*sizeof(Vertex) );
}

void VertexBuffer::bind() const{
    m_buffer->bind();
}

VertexBuffer::~VertexBuffer(){
    delete m_buffer;
}
